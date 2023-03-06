#include <ESP8266WiFi.h>
#include "FirebaseArduino.h"

#define FIREBASE_HOST "iot-project-c5068-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_AUTH "3qE8tY6JkbSati1lljEPiOrxXrc1WzoDvUoqvt2K"
#define WIFI_SSID "*IL MOORO*"
#define WIFI_PASSWORD "01234567"

const int flame = D0; 
const int buzz = D1;

void setup(){
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(flame, INPUT_PULLUP); // PIR sensor as input  
  digitalWrite (buzz, LOW);// Initially buzzer off
  digitalWrite (flame, LOW);// Initially buzzer off

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop(){
    int val = digitalRead(flame);
    bool checkStatus=(Firebase.getBool("Alarm/Status"));
    Serial.print("Status: ");
    Serial.println(checkStatus);  
    Serial.print("Status od read value of sensor: ");
    Serial.println(val);  
  
    if(val==0){
      checkStatus=true;
     }
  else{
    if(checkStatus!=true){
     checkStatus=false;
      }
    }
    if(checkStatus){
      tone(buzz,432,3000);
      digitalWrite(flame,0);
    
      Firebase.setBool("Alarm/Status", true);
     
      if (Firebase.failed()) {
        Serial.print("Nije uspjelo slanje povratne informacije: ");
        Serial.println(Firebase.error()); 
      }
      Serial.println("Fire detected!");
    
    }   
    else{
      tone(buzz,0,0);
      digitalWrite(flame,1);
      Firebase.setBool("Alarm/Status", false);
     
      if (Firebase.failed()) {
        Serial.print("Nije uspjelo slanje povratne informacije: ");
        Serial.println(Firebase.error());  
      }
    
      Serial.println("Extinguished the fire.");
    }    
    delay(1000);
 }
