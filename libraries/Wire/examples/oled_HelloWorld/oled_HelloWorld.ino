//https://www.electroniclinic.com/arduino-oled-i2c-display-128x64-with-examples-wiring-and-libraries-issues-solved/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);
/*
 * link to refer: https://www.electroniclinic.com/arduino-oled-i2c-display-128x64-with-examples-wiring-and-libraries-issues-solved/
 * Use Adafruit_SSD1306 library instead of Adafruit_SSD1106 for this code to run
 */


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
 
}

void loop() {
 
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(1,20);
display.print("Hello World!");
display.display();
  
}
