/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Fri, 02 Apr 2021 06:36:59 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/

#include <Wire.h>

int buttonState;

int lastState;

byte myRead=0;
byte myLEDs[]={16,8,4,2,1,128,64,32};
byte allLEDs=255;
byte ledAddr=0x20;

void lightOn(byte myLED,byte LED_on){
  byte myTempByte=0;
  Wire.requestFrom((int)ledAddr, 1);
  myRead=Wire.read();
  Wire.beginTransmission((int)ledAddr);
  if (LED_on==1)
    myTempByte=(myRead & ~myLEDs[myLED]);
  else if (LED_on==0)
    myTempByte=(myRead | myLEDs[myLED]);
  Wire.write(myTempByte);
  Wire.endTransmission();
}

void setup()
{
  Serial.begin(9600);

  buttonState = 0;
  lastState = 0;
  pinMode(5, INPUT);
  Wire.begin(26,27);
}


void loop()
{
  buttonState = digitalRead(5);
  Serial.println(lastState);
  if (buttonState == true) {
    lastState = !lastState;
    lightOn(7,lastState);

  }
}