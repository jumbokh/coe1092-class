/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 14 Apr 2021 01:58:07 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

float now_time;

float run_time;

float temperature;

int humidity;

char _lwifi_ssid[] = "gigaenergy";
char _lwifi_pass[] = "12369874";
#define MQTT_SERVER_IP "gpssensor.ddns.net"
#define MQTT_SERVER_PORT 1883
#define MQTT_ID "jumbokh"
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
String receivedTopic="";
String receivedMsg="";
bool waitForE=true;
bool ended=true;
bool pubCtrl=false;

WiFiClient mqttClient;
PubSubClient myClient(mqttClient);

void connectMQTT(){
  while (!myClient.connected()){
    if (!myClient.connect(MQTT_ID,MQTT_USERNAME,MQTT_PASSWORD))
    {
      delay(5000);
    }
  }
}

DHT dht11_p5(5, DHT11);

void mqttCallback(char* topic, byte* payload, unsigned int length){
  receivedTopic=String(topic);
  receivedMsg="";
  for (unsigned int myIndex = 0; myIndex < length; myIndex++)
  {
      receivedMsg += (char)payload[myIndex];
  }
  receivedMsg.trim();
  if (receivedMsg == "1") {
    digitalWrite(2, HIGH);
    digitalWrite(1,HIGH);

  } else if (receivedMsg == "0") {
    digitalWrite(2, LOW);
    digitalWrite(1,LOW);
  }

}

void setup()
{
  myClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  myClient.setCallback(mqttCallback);

  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  connectMQTT();
  myClient.subscribe(String("jumbokh/light").c_str());
  run_time = millis();
  dht11_p5.begin();
  pinMode(2, OUTPUT);
  pinMode(1,OUTPUT);
}


void loop()
{
  myClient.loop();
  now_time = millis();
  if (now_time - run_time >= 2000) {
    temperature = dht11_p5.readTemperature();
    myClient.publish(String("jumbokh/T").c_str(),String(String() + temperature).c_str());
    humidity = dht11_p5.readHumidity();
    myClient.publish(String("jumbokh/H").c_str(),String(String() + humidity).c_str());
    delay(300);
    run_time = millis();

  }
}