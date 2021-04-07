/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 07 Apr 2021 01:59:41 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/

#include <DHT.h>

DHT dht11_p5(5, DHT11);

void setup()
{
  Serial.begin(115200);

  delay(5000);
  dht11_p5.begin();
}


void loop()
{
  Serial.print("溫度:");
  Serial.println(dht11_p5.readTemperature());
  Serial.print("濕度:");
  Serial.println(dht11_p5.readHumidity());
  delay(1000);
}