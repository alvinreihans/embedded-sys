#define BLYNK_TEMPLATE_ID "TMPL62mVNYmC6"
#define BLYNK_TEMPLATE_NAME "Final Project"
#define BLYNK_AUTH_TOKEN "EL0-lFcxLeQVqUPqoHuQaTHNveDozTGG"
#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <ESP8266WiFi.h>

int smokeSensor = A0;

int flameSensor = D0;

#define waterpump D6
#define buzzerPin D5

#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "ARMA laptop";
char pass[] = "1234567890";

void setup() {
   Serial.begin(9600);
   Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
   dht.begin();
   pinMode(flameSensor, INPUT);
   pinMode(smokeSensor, INPUT);
   pinMode(waterpump, OUTPUT);
   pinMode(buzzerPin, OUTPUT);
   digitalWrite(buzzerPin, LOW);
   digitalWrite(waterpump, LOW);  // HIGH = OFF
}

void loop() {
   //=====DHT========
   float tempValue = dht.readTemperature();
   Blynk.virtualWrite(V0, tempValue);
   //=====MQ2========
   int gasValue = analogRead(smokeSensor);
   Blynk.virtualWrite(V1, gasValue);
   //=====FLAME========
   int flameValue = digitalRead(flameSensor);

   //=====CONDITION LOGIC: DANGER1========
   if ((tempValue >= 40 || gasValue >= 500) && flameValue == 0) {
      Blynk.virtualWrite(V4, "DANGER!");
      Blynk.virtualWrite(V2, "True");
      digitalWrite(waterpump, LOW);
      digitalWrite(buzzerPin, HIGH);
      delay(750);
      digitalWrite(buzzerPin, LOW);
      Blynk.virtualWrite(V4, "FIRE DETECTED!");
   }
   //=====CONDITION LOGIC: DANGER2========
   else if (flameValue == 0) {
      Blynk.virtualWrite(V4, "DANGER!");
      Blynk.virtualWrite(V2, "True");
      digitalWrite(waterpump, LOW);
      digitalWrite(buzzerPin, HIGH);
      delay(750);
      digitalWrite(buzzerPin, LOW);
      Blynk.virtualWrite(V4, "FIRE DETECTED!");
   }
   //=====CONDITION LOGIC: WARNING1========
   else if (gasValue >= 500) {
      Blynk.virtualWrite(V4, "WARNING!");
      Blynk.virtualWrite(V2, "False");
      digitalWrite(waterpump, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(750);
      digitalWrite(buzzerPin, LOW);
      Blynk.virtualWrite(V4, "GAS LEAK DETECTED!");

   }
   //=====CONDITION LOGIC: WARNING2========
   else if (tempValue >= 40) {
      Blynk.virtualWrite(V4, "WARNING!");
      Blynk.virtualWrite(V2, "False");
      digitalWrite(waterpump, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(750);
      digitalWrite(buzzerPin, LOW);
      Blynk.virtualWrite(V4, "HIGH TEMPERATURE DETECTED!");
   }
   //=====CONDITION LOGIC: SAFE========
   else {
      Blynk.virtualWrite(V4, "Safe");
      Blynk.virtualWrite(V2, "False");
      digitalWrite(waterpump, HIGH);
      digitalWrite(buzzerPin, LOW);
      delay(750);
   }
   delay(750);
   Blynk.run();
}