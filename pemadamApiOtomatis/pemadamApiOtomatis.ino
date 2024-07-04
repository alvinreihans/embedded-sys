#define BLYNK_TEMPLATE_ID "TMPL61AWu3azS"
#define BLYNK_TEMPLATE_NAME "DHT device"
#define BLYNK_AUTH_TOKEN "A7um68amYCDUzqfEPJa5EEbUnZw0Vf94"
#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <MQ2.h>
#include <Servo.h>
#define flameSensor D1
#define MQ2sensor D2
#define waterpump D4
#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
MQ2 gasSensor(MQ2sensor);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "ARMA laptop";
char pass[] = "1234567890";
BlynkTimer timer;

void setup() {
   Serial.begin(9600);
   Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
   dht.begin();
   pinMode(flameSensor, INPUT);
   pinMode(MQ2sensor, INPUT);
   pinMode(waterpump, OUTPUT);
   timer.setInterval(1000L, sendSensor);
}

void loop() {
   Blynk.run();
   timer.run();
}

void sendSensor() {
   //=====DHT========
   float tempValue = dht.readTemperature();
   if (isnan(tempValue)) {
      Serial.println("Failed to read from DHT sensor!");
   }
   Blynk.virtualWrite(V0, tempValue);
   //=====MQ2========
   int gasValue = analogRead(MQ2sensor) * 9.47;
   Blynk.virtualWrite(V1, gasValue);
   //=====FLAME========
   int flameValue = digitalRead(flameSensor);
   //=====CONDITION LOGIC: DANGER========
   if ((tempValue >= 40 || gasValue >= 500) && flameValue == 0) {
      Blynk.virtualWrite(V4, "DANGER!");
      delay(750);
      Blynk.virtualWrite(V4, "FIRE DETECTED!");
      delay(750);
   }
   //=====CONDITION LOGIC: WARNING1========
   else if (gasValue >= 500) {
      Blynk.virtualWrite(V4, "WARNING!");
      delay(750);
      Blynk.virtualWrite(V4, "GAS LEAK DETECTED!");
      delay(750);
   }
   //=====CONDITION LOGIC: WARNING2========
   else if (tempValue >= 40) {
      Blynk.virtualWrite(V4, "WARNING!");
      delay(750);
      Blynk.virtualWrite(V4, "SMOKE DETECTED!");
      delay(750);
   }
   //=====CONDITION LOGIC: SAFE========
   else {
      Blynk.virtualWrite(V4, "Safe");
      delay(1500);
   }
}