/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sat, 03 Apr 2021 08:15:34 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/



float refvol;

int rctime;

float vin;

float total_time;

float voltage;

void setup()
{
  Serial.begin(9600);

  refvol = 3.3;
  vin = 0;
  total_time = 0;
}


void loop()
{
  rctime = millis();
  vin = analogRead(36);
  voltage = vin * refvol;
  voltage = voltage / 4096;
  Serial.print((rctime / 1000));
  Serial.print(", ");
  Serial.println(voltage);
}