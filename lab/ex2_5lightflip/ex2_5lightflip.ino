/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Tue, 30 Mar 2021 03:06:57 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/

#include <Wire.h>

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

  Wire.begin(26,27);
}


void loop()
{
  lightOn(0,HIGH);
  delay(1000);
  lightOn(1,HIGH);
  delay(1000);
  lightOn(2,HIGH);
  delay(1000);
  lightOn(3,HIGH);
  delay(1000);
  lightOn(4,HIGH);
  delay(1000);
  lightOn(4,LOW);
  lightOn(3,LOW);
  lightOn(2,LOW);
  lightOn(1,LOW);
  lightOn(0,LOW);
  delay(2000);
}