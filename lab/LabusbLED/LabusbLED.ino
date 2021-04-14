/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 14 Apr 2021 01:43:14 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/



int  i;

void setup()
{
  pinMode(1,OUTPUT);
  for (i = 0; i <= 10; i++) {
    digitalWrite(1,HIGH);
    delay(1000);
    digitalWrite(1,LOW);
    delay(1000);
  }
}


void loop()
{

}