/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 07 Apr 2021 02:25:51 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd_i2c(0x27);

int counter;

void setup()
{
  lcd_i2c.begin(16, 2);
  counter = 0;
}


void loop()
{
  lcd_i2c.clear();
  lcd_i2c.setCursor(0,0);
  lcd_i2c.print("HELLO");
  lcd_i2c.setCursor(0,1);
  lcd_i2c.print(String() + "ESP32: " + counter);
  counter = counter + 1;
  delay(1000);
}