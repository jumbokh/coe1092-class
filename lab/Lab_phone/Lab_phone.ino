/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 14 Apr 2021 08:15:08 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/

#include <LRemote.h>

LRemoteLabel label1;
LRemoteButton button1;

void setup()
{
  LRemote.setName("ESP32 Jumbo");
  LRemote.setOrientation(RC_PORTRAIT);
  LRemote.setGrid(3, 5);
    label1.setPos(0, 0);
    label1.setText("按鈕測試");
    label1.setSize(3, 1);
    label1.setColor(RC_ORANGE);
    LRemote.addControl(label1);

    button1.setPos(0, 2);
    button1.setText("按下點亮");
    button1.setSize(3, 2);
    button1.setColor(RC_BLUE);
    LRemote.addControl(button1);
  LRemote.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop()
{
  LRemote.process();
  if (button1.isValueChanged()) {
    if (button1.getValue() == 1) {
      digitalWrite(LED_BUILTIN, HIGH);

    } else {
      digitalWrite(LED_BUILTIN, LOW);

    }

  }
}