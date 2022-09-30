#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
TwoWire Wire(1);


void sensor_setup() {
  bmp.begin();
}

int getSensorData() {
int temp = bmp.readTemperature();
return temp;
}
