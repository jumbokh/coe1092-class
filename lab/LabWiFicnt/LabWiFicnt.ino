/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 14 Apr 2021 02:12:02 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/

#include <WiFi.h>

String ipaddr;

char _lwifi_ssid[] = "gigaenergy";
char _lwifi_pass[] = "12369874";

void setup()
{
  pinMode(1,OUTPUT);
  Serial.begin(115200);

  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  digitalWrite(1,LOW);
  ipaddr = WiFi.localIP().toString();
  Serial.println(String() + "IP:" + ipaddr);
  if (ipaddr != "0.0.0.0") {
    digitalWrite(1,HIGH);
    delay(5000);
    digitalWrite(1,LOW);

  }
}


void loop()
{

}