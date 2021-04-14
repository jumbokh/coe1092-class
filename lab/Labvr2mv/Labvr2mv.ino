/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 14 Apr 2021 06:39:00 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/



int input;

void setup()
{

  Serial.begin(9600);

}


void loop()
{
  input = analogRead(36);
  Serial.print("輸入電壓: ");
  Serial.print(((input * 3300) / 4096));
  Serial.println("mV");
  delay(1000);
}