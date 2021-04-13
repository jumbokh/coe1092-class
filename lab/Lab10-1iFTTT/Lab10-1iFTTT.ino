#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
//pls use sketch/include library/manage library find simpledht by winlin 
//or you can use another library
#include <SimpleDHT.h>
int pinDHT11 = 2; //set dht11 at pin2
SimpleDHT11 dht11(pinDHT11);

WiFiMulti wifiMulti;
char* WifiSSID="YouSSID";
char* WifiPassword="YouPassword";
//1.replace https with http 
//2.replace youreventname with your  event name
//3.replace yourkey at the end of url with your key
String IFTTTUrl="http://maker.ifttt.com/trigger/youreventname/with/key/yourkey";
void setup() {
    Serial.begin(115200);
    Serial.println();
    wifiMulti.addAP(WifiSSID, WifiPassword);  
    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }
}

void loop() {
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {
        //=======Reading dht11 data==============
        Serial.println("reading DHT11...");
        byte temperature = 0;
        byte humidity = 0;
        int err = SimpleDHTErrSuccess; 
        //reading data
        if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
          Serial.print("Read DHT11 failed, err="); Serial.println(err);
          return;//dht read error
        }
        Serial.print("Reading OK: ");      
        //=======dht11 data read==========
        //regenerate url string with temp and humd
        String url=IFTTTUrl+"?value1="+String((int)temperature)+"&value2="+String((int)humidity);        

        //Start to send data to IFTTT
        HTTPClient http;
        Serial.print("[HTTP] begin...\n");
        http.begin(url); //HTTP

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();
        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    }
    delay(30000);//send data every 20 seconds
}