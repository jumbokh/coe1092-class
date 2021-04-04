/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Fri, 02 Apr 2021 03:21:36 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/

int buttonState = 0;         // variable for reading the pushbutton status

void setup()
{
  pinMode(5,INPUT_PULLUP);
  pinMode(2, OUTPUT);
}


void loop()
{
  buttonState = digitalRead(buttonPin);
   if (buttonState == HIGH) {
     digitalWrite(2, HIGH);
  } else {
  digitalWrite(2, LOW);
  }
}
