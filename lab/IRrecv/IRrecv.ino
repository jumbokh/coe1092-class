/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Mon, 05 Apr 2021 08:58:20 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/

#include <IRremote.h>

IRrecv irrecv(14);
decode_results results;
String myCodeType;
String myIRcode;
String ir_type(int tip)
{
  if (tip == 1){
    return "RC5";
  } else if (tip == 2){
    return "RC6";
  } else if (tip == 3){
    return "NEC";
  } else if (tip == 4){
    return "SONY";
  } else if (tip == 5){
    return "PANASONIC";
  } else if (tip == 6){
    return "JVC";
  } else if (tip == 7){
    return "SAMSUNG";
  } else if (tip == 10){
    return "LG";
  } else if (tip == 14){
    return "SHARP";
  } else if (tip == 17){
    return "LEGO_PF";
  } else {
    return "UNKNOWN";
  }
}

void setup()
{
  irrecv.enableIRIn();

  Serial.begin(115200);


}


void loop()
{
  if (irrecv.decode(&results)) {
    if (results.decode_type>0){
      myCodeType=ir_type(results.decode_type);
      myIRcode=String(results.value, HEX);
      if (myIRcode != "ffffffff") {
        Serial.println(String() + "紅外線類型:" + myCodeType);
        Serial.println(String() + "紅外線編碼:" + myIRcode);

      }
    }
    irrecv.resume();
  }
}