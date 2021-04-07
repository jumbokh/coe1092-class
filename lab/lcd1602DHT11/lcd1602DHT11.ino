/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 07 Apr 2021 02:33:53 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd_i2c(0x27);

#include <DHT.h>

DHT dht11_p5(5, DHT11);

void setup()
{
  lcd_i2c.begin(16, 2);
  lcd_i2c.clear();
  dht11_p5.begin();
}


void loop()
{
  lcd_i2c.setCursor(0,0);
  lcd_i2c.print(String() + "Temp.: " + dht11_p5.readTemperature());
  lcd_i2c.setCursor(0,1);
  lcd_i2c.print(String() + "Humi.: " + dht11_p5.readHumidity());
  delay(1000);
}