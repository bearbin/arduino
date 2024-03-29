/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED 7-Segment backpacks 
  ----> http://www.adafruit.com/products/881
  ----> http://www.adafruit.com/products/880
  ----> http://www.adafruit.com/products/879
  ----> http://www.adafruit.com/products/878

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// Enable one of these two #includes and comment out the other.
// Conditional #include doesn't work due to Arduino IDE shenanigans.
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  Serial.begin(9600);
  matrix.begin(0x70);
  matrix.setBrightness(5);
}

void loop() {
  String temp = "";
  while (Serial.available()) {
    temp.concat(Serial.read() - '0');
    delay(5);
  }
  if (temp != "") {
    int num = atoi(temp.c_str());
    matrix.writeDigitNum(0, -1, false);
    matrix.writeDigitNum(1, num/(int)100, false);
    matrix.writeDigitNum(3, (num%100)/(int)10, true);
    matrix.writeDigitNum(4, (num%10), false);
    matrix.writeDisplay();
  }
}
