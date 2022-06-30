unsigned char ByteReceived; // declare a variable
void setup(){ 
  // put your setup code here, to run once:
  Serial.begin(9600);  // Initialize Serial Monitor 
  //Prompt the messages for user
  Serial.println("--- Start Serial Monitor Communication ---");
  Serial.println(" Type some random data in above text box");
  Serial.println("Arduino will print out the data which you enter in above text box in below order/format");
  Serial.println("(Decimal)(Hex)(Character)");  
  Serial.println(); 
}
void loop(){
  // put your main code here, to run repeatedly:
 // if (Serial.available() > 0)           //Wait for user input
  { 
    ByteReceived = Serial.read();       //Read user input and hold it in a variable
    Serial.print(ByteReceived);         //Print decimal value of user input
    Serial.print("        ");           //Add some space 
    Serial.print(ByteReceived, HEX);    //Print the hex value of user input
    Serial.print("       ");            //Add some space
    Serial.print(char(ByteReceived));   //Print the character value of user input 
    Serial.println();                   //Move cursor to new line  
  }
}
