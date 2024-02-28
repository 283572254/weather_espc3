/**
 * Authorization.ino
 *
 *  Created on: 09.12.2015
 *
 */

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include<Adafruit_SSD1306.h>
#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;
DynamicJsonDocument doc(1024);
String Weather = "0";                //
void setup() {

    USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();
    
    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP("Redmi K60", "201910088047");

}

void loop() {
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url


        http.begin("https://api.seniverse.com/v3/weather/now.json?key=SO6JJ18X9WSJVbJWg&location=%E5%B9%BF%E5%B7%9E&language=zh-Hans&unit=c");

        /*
          // or
          http.begin("http://192.168.1.12/test.html");
          http.setAuthorization("user", "password");

          // or
          http.begin("http://192.168.1.12/test.html");
          http.setAuthorization("dXNlcjpwYXN3b3Jk");
         */


        USE_SERIAL.print("���� GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();
         USE_SERIAL.println(httpCode);
        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("���� GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
                deserializeJson(doc, payload);
                Weather = doc["results"][0]["now"]["text"].as<String>();               //����
                
                Serial.println(Weather);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(10000);
}

