/*
 * ESP8266 AT
 * http://www.electronicwings.com
 */ 
#include "ESP8266_AT.h"


UARTClass esp(1);

int8_t Response_Status;
uint32_t TimeOut = 0;
char RESPONSE_BUFFER[DEFAULT_BUFFER_SIZE];

void Read_Response(char* _Expected_Response)
{
	Serial.println("Inside Read_Response()");

	uint8_t ch, EXPECTED_RESPONSE_LENGTH = strlen(_Expected_Response);
	uint32_t TimeCount = millis();
	uint16_t Buffindex=0;
	char RECEIVED_CRLF_BUF[EXPECTED_RESPONSE_LENGTH];
	Serial.println("Inside Read_Response() :: Checkpoint_1");
	while(1)
	{
		Serial.println("Inside Read_Response() :: Checkpoint_2");
		if((DEFAULT_TIMEOUT+TimeOut) <= (millis()-TimeCount))
		{
			Serial.println("Inside Read_Response() :: Checkpoint_3");
			TimeOut = 0;
			Response_Status = ESP8266_RESPONSE_TIMEOUT;
			return;
		}
		if(Response_Status == ESP8266_RESPONSE_STARTING)
		{
			Serial.println("Inside Read_Response() :: Checkpoint_4");
			Response_Status = ESP8266_RESPONSE_WAITING;
		}
		
		while(1)
		{
			Serial.println("Inside Read_Response() :: Checkpoint_5");
			ch = esp.read();
			Serial.println("Inside Read_Response() :: Checkpoint_6");
			RESPONSE_BUFFER[Buffindex++] = ch;
			memmove(RECEIVED_CRLF_BUF, RECEIVED_CRLF_BUF + 1, EXPECTED_RESPONSE_LENGTH-1);
			RECEIVED_CRLF_BUF[EXPECTED_RESPONSE_LENGTH-1] = ch;
			if(!strncmp(RECEIVED_CRLF_BUF, _Expected_Response, EXPECTED_RESPONSE_LENGTH))
			{
				Serial.println("Inside Read_Response() :: Checkpoint_7");
				TimeOut = 0;
				Response_Status = ESP8266_RESPONSE_FINISHED;
				return;
			}
		}
	}
	Serial.println("Inside Read_Response() :: Checkpoint_8");
}

void ESP8266_Clear()
{
	Serial.println("Inside ESP8266_Clear()");
	while(esp.available()>0) esp.read();
	Serial.println("Inside ESP8266_Clear() :: Checkpoint_1");
	memset(RESPONSE_BUFFER,0,DEFAULT_BUFFER_SIZE);
	Serial.println("Inside ESP8266_Clear() :: Checkpoint_2");
}

void Start_Read_Response(char* _ExpectedResponse)
{
	Serial.println("Inside Start_Read_Response()");
	Response_Status = ESP8266_RESPONSE_STARTING;
	do {
		Read_Response(_ExpectedResponse);
		Serial.println("Inside Start_Read_Response() :: Checkpoint_1");
	} while(Response_Status == ESP8266_RESPONSE_WAITING);
	Serial.println("Inside Start_Read_Response() :: Checkpoint_2");	
}

void GetResponseBody(char* Response, uint16_t ResponseLength)
{

	uint16_t i = 12;
	char buffer[5];
	while(Response[i] != '\r')
	++i;

	strncpy(buffer, Response + 12, (i - 12));
	ResponseLength = atoi(buffer);

	i += 2;
	uint16_t tmp = strlen(Response) - i;
	memcpy(Response, Response + i, tmp);

	if(!strncmp(Response + tmp - 6, "\r\nOK\r\n", 6))
	memset(Response + tmp - 6, 0, i + 6);
}

bool WaitForExpectedResponse(char* ExpectedResponse)
{
	Serial.println("Inside WaitForExpectedResponse()");
	Start_Read_Response(ExpectedResponse);	/* First read response */
	Serial.println("Inside WaitForExpectedResponse() :: Checkpoint_1");
	if((Response_Status != ESP8266_RESPONSE_TIMEOUT)){
		Serial.println("Inside WaitForExpectedResponse() :: Checkpoint_2");
		return true;							/* Return true for success */
	}
	Serial.println("Inside WaitForExpectedResponse() :: Checkpoint_3");
	return false;							/* Else return false */
}

bool SendATandExpectResponse(char* ATCommand, char* ExpectedResponse)
{
	Serial.println("Inside SendATandExpectResponse()");
	ESP8266_Clear();
	Serial.println(ATCommand);			/* Send AT command to ESP8266 */
	return WaitForExpectedResponse(ExpectedResponse);
}

bool ESP8266_ApplicationMode(uint8_t Mode)
{
	char _atCommand[20];
	memset(_atCommand, 0, 20);
	sprintf(_atCommand, "AT+CIPMODE=%d", Mode);
	_atCommand[19] = 0;
	return SendATandExpectResponse(_atCommand, "\r\nOK\r\n");
}

bool ESP8266_ConnectionMode(uint8_t Mode)
{
	char _atCommand[20];
	memset(_atCommand, 0, 20);
	sprintf(_atCommand, "AT+CIPMUX=%d", Mode);
	_atCommand[19] = 0;
	return SendATandExpectResponse(_atCommand, "\r\nOK\r\n");
}

bool ESP8266_Begin()
{
	Serial.println("Inside ESP8266_Begin()");
	for (uint8_t i=0;i<5;i++)
	{
		Serial.println("Inside ESP8266_Begin() :: Checkpoint_1");
		if(SendATandExpectResponse("ATE0","\r\nOK\r\n")||SendATandExpectResponse("AT","\r\nOK\r\n")){
			Serial.println("Inside ESP8266_Begin() :: Checkpoint_2");
			return true;
		}
	}
	Serial.println("Inside ESP8266_Begin() :: Checkpoint_3");
	return false;
}

bool ESP8266_Close()
{
	return SendATandExpectResponse("AT+CIPCLOSE=1", "\r\nOK\r\n");
}

bool ESP8266_WIFIMode(uint8_t _mode)
{
	char _atCommand[20];
	memset(_atCommand, 0, 20);
	sprintf(_atCommand, "AT+CWMODE=%d", _mode);
	_atCommand[19] = 0;
	return SendATandExpectResponse(_atCommand, "\r\nOK\r\n");
}

uint8_t ESP8266_JoinAccessPoint(char* _SSID, char* _PASSWORD)
{
	char _atCommand[60];
	memset(_atCommand, 0, 60);
	sprintf(_atCommand, "AT+CWJAP=\"%s\",\"%s\"", _SSID, _PASSWORD);
	_atCommand[59] = 0;
	if(SendATandExpectResponse(_atCommand, "\r\nWIFI CONNECTED\r\n"))
	return ESP8266_WIFI_CONNECTED;
	else{
		if(strstr(RESPONSE_BUFFER, "+CWJAP:1"))
		return ESP8266_CONNECTION_TIMEOUT;
		else if(strstr(RESPONSE_BUFFER, "+CWJAP:2"))
		return ESP8266_WRONG_PASSWORD;
		else if(strstr(RESPONSE_BUFFER, "+CWJAP:3"))
		return ESP8266_NOT_FOUND_TARGET_AP;
		else if(strstr(RESPONSE_BUFFER, "+CWJAP:4"))
		return ESP8266_CONNECTION_FAILED;
		else
		return ESP8266_JOIN_UNKNOWN_ERROR;
	}
}

uint8_t ESP8266_connected()
{
	SendATandExpectResponse("AT+CIPSTATUS", "\r\nOK\r\n");
	if(strstr(RESPONSE_BUFFER, "STATUS:2"))
	return ESP8266_CONNECTED_TO_AP;
	else if(strstr(RESPONSE_BUFFER, "STATUS:3"))
	return ESP8266_CREATED_TRANSMISSION;
	else if(strstr(RESPONSE_BUFFER, "STATUS:4"))
	return ESP8266_TRANSMISSION_DISCONNECTED;
	else if(strstr(RESPONSE_BUFFER, "STATUS:5"))
	return ESP8266_NOT_CONNECTED_TO_AP;
	else
	return ESP8266_CONNECT_UNKNOWN_ERROR;
}

uint8_t ESP8266_Start(uint8_t _ConnectionNumber, char* Domain, char* Port)
{
	bool _startResponse;
	char _atCommand[60];
	memset(_atCommand, 0, 60);
	_atCommand[59] = 0;

	if(SendATandExpectResponse("AT+CIPMUX?", "CIPMUX:0"))
	sprintf(_atCommand, "AT+CIPSTART=\"TCP\",\"%s\",%s", Domain, Port);
	else
	sprintf(_atCommand, "AT+CIPSTART=\"%d\",\"TCP\",\"%s\",%s", _ConnectionNumber, Domain, Port);

	_startResponse = SendATandExpectResponse(_atCommand, "CONNECT\r\n");
	if(!_startResponse)
	{
		if(Response_Status == ESP8266_RESPONSE_TIMEOUT)
		return ESP8266_RESPONSE_TIMEOUT;
		return ESP8266_RESPONSE_ERROR;
	}
	return ESP8266_RESPONSE_FINISHED;
}

uint8_t ESP8266_Send(char* Data)
{
	char _atCommand[20];
	memset(_atCommand, 0, 20);
	sprintf(_atCommand, "AT+CIPSEND=%d", (strlen(Data)+2));
	_atCommand[19] = 0;
	SendATandExpectResponse(_atCommand, "\r\nOK\r\n>");
	if(!SendATandExpectResponse(Data, "\r\nSEND OK\r\n"))
	{
		if(Response_Status == ESP8266_RESPONSE_TIMEOUT)
		return ESP8266_RESPONSE_TIMEOUT;
		return ESP8266_RESPONSE_ERROR;
	}
	return ESP8266_RESPONSE_FINISHED;
}

uint16_t Read_Data(char* _buffer)
{
	uint16_t len = 0;
	delay(100);
	while(Serial.available() > 0)
	_buffer[len++] = esp.read();
	return len;
}
