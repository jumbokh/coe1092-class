/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Wed, 14 Apr 2021 16:23:33 GMT
 */

/*

 * 部份程式碼由吉哥積木產生
 * https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697

*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <DHT.h>
#include <WiFiUdp.h>
#include <ctime>

float now_time;

float temperature;

float run_time;

int humidity;

char _lwifi_ssid[] = "Tenda_5295A0";
char _lwifi_pass[] = "0953313123";
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

byte myRead=0;
byte myLEDs[]={16,8,4,2,1,128,64,32};
byte allLEDs=255;
byte ledAddr=0x20;

void lightOn(byte myLED,byte LED_on){
  byte myTempByte=0;
  Wire.requestFrom((int)ledAddr, 1);
  myRead=Wire.read();
  Wire.beginTransmission((int)ledAddr);
  if (LED_on==1)
    myTempByte=(myRead & ~myLEDs[myLED]);
  else if (LED_on==0)
    myTempByte=(myRead | myLEDs[myLED]);
  Wire.write(myTempByte);
  Wire.endTransmission();
}

DHT dht11_p5(5, DHT11);

const char *NTP_server = "time.stdtime.gov.tw";
const int NTP_PACKET_SIZE = 48;                   // NTP time stamp is in the first 48 bytes of the message
static byte packetBuffer[NTP_PACKET_SIZE] = {0};  //buffer to hold incoming and outgoing packets
const unsigned int localPort = 2390;              // local port to listen for UDP packets
static WiFiUDP Udp;                               // A UDP instance to let us send and receive packets over UDP

String getNetworkTime() {
  Udp.begin(localPort);
  sendNTPpacket(NTP_server); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);
  if (Udp.parsePacket()) {
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:
    const unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    const unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    const unsigned long secsSince1900 = highWord << 16 | lowWord;
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    const unsigned long epoch = secsSince1900 - seventyYears;
    // Taiwan is UTC+8 = 8 * 60 * 60 seconds
    const time_t taiwan_time = epoch + (8 * 60 * 60);
    // const tm* pTime = gmtime(&taiwan_time);
    static char time_text[] = "YYYY-MM-DDTHH:MM:SS+08";
    strftime(time_text, sizeof(time_text), "%Y-%m-%dT%H:%M:%S+08", gmtime(&taiwan_time));
    return String((const char*)time_text);
  }

  return String("Connection error");
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(const char* host) {
	//Serial.println("1");
	// set all bytes in the buffer to 0
	memset(packetBuffer, 0, NTP_PACKET_SIZE);
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	//Serial.println("2");
	packetBuffer[0] = 0b11100011;   // LI, Version, Mode
	packetBuffer[1] = 0;     // Stratum, or type of clock
	packetBuffer[2] = 6;     // Polling Interval
	packetBuffer[3] = 0xEC;  // Peer Clock Precision
	// 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer[12]  = 49;
	packetBuffer[13]  = 0x4E;
	packetBuffer[14]  = 49;
	packetBuffer[15]  = 52;

	//Serial.println("3");

	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp:
	Udp.beginPacket(host, 123); //NTP requests are to port 123
	//Serial.println("4");
	Udp.write(packetBuffer, NTP_PACKET_SIZE);
	//Serial.println("5");
	Udp.endPacket();
	//Serial.println("6");

	return 0;
}

void mqttCallback(char* topic, byte* payload, unsigned int length){
  receivedTopic=String(topic);
  receivedMsg="";
  for (unsigned int myIndex = 0; myIndex < length; myIndex++)
  {
      receivedMsg += (char)payload[myIndex];
  }
  receivedMsg.trim();
  Serial.println(String() + "收到 MQTT Topic:" + receivedTopic + receivedMsg);
  if (receivedTopic == "jumbokh/light") {
    if (receivedMsg == "1") {
      digitalWrite(1,HIGH);
      lightOn(7,HIGH);

    } else if (receivedMsg == "0") {
      digitalWrite(1,LOW);
      lightOn(7,LOW);
    }

  } else if (receivedTopic == "jumbokh/fan") {
    if (receivedMsg == "1") {
      digitalWrite(3,HIGH);
      lightOn(5,HIGH);

    } else if (receivedMsg == "0") {
      digitalWrite(3,LOW);
      lightOn(5,LOW);
    }
  }

}

void setup()
{
  Serial.begin(115200);

  myClient.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  myClient.setCallback(mqttCallback);

  pinMode(1,OUTPUT);
  pinMode(3,OUTPUT);
  Wire.begin(26,27);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  Serial.println(String() + "IP:" + WiFi.localIP().toString());
  while (myClient.connected() == false) {
    connectMQTT();
  }
  Serial.println(String() + "MQTT 連接:" + myClient.connected());
  delay(5000);
  myClient.subscribe(String("jumbokh/light").c_str());
  myClient.subscribe(String("jumbokh/fan").c_str());
  digitalWrite(1,LOW);
  digitalWrite(3,LOW);
  lightOn(7,LOW);
  lightOn(5,LOW);
  run_time = millis();
  dht11_p5.begin();
}


void loop()
{
  myClient.loop();
  now_time = millis();
  if (now_time - run_time >= 30000) {
    temperature = dht11_p5.readTemperature();
    myClient.publish(String("jumbokh/T").c_str(),String(String() + temperature).c_str());
    humidity = dht11_p5.readHumidity();
    myClient.publish(String("jumbokh/H").c_str(),String(String() + humidity).c_str());
    Serial.println(String() + getNetworkTime() + ", T=" + temperature + ", H=" + humidity);
    delay(300);
    run_time = millis();

  }
}