/**
 @file usb_tx_rx.ino
 @brief contains routines for UART USB interface
 @detail Includes software functions declarations to initialize,configure, write and read through USB over UART interface

 * Reference arduino code: 
 * Refrence aries board: 
 * Transmit and reception using 2 usb through aries board.The program is configured for transmitting data from usb0
 * which is the default usb port for aries and the transmitted data will be displayed on usb1. Can set up terminal 
 * as usb1 for displaying the data.
 * Device address -0x50
 * Connections:
 * USB     Aries Board
 * 3V3      -   3.3V
 * GND      -   GND
 * Tx       -   Rx1
 * Rx       -   Tx1
 * For connecting to port 2 (Tx 2 and Rx 2) of aries board use the function  UARTClass usb(2) instead of UARTClass usb(1);
 * .
 **/

#include <UARTClass.h>

UARTClass usb(1);

unsigned char ByteReceived; // declare a variable
void setup(){ 
  // put your setup code here, to run once:
  Serial.begin(115200);  // Initialize Serial Monitor 
  usb.begin(115200);
  //Prompt the messages for user
  Serial.println("--- Start Serial Monitor Communication ---");
  Serial.println(" Type some random data in above text box");
  Serial.println("Arduino will print out the data which you enter in above text box in below order/format");
  Serial.println("(Decimal)(Hex)(Character)");  
  Serial.println(); 
}
void loop(){
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)           //Wait for user input
  { 
    ByteReceived = Serial.read();       //Read user input and hold it in a variable
   usb.print(char(ByteReceived));   //Print the character value of user input 
                    
  }
}
