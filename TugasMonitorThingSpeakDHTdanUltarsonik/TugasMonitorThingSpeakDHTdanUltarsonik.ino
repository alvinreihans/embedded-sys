#include <ESP8266WiFi.h>
#include "DHT.h"
#include "ThingSpeak.h"
#define DHTPIN D4
#define DHTTYPE DHT11
#define triggerPin D8
#define echoPin D7

DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "ARMA laptop";
const char* password = "1234567890";
unsigned long myChannelNumber = 2308449;
const char* myWriteAPIKey = "WUELHRQ7AVICL64V";
WiFiClient client;

void setup() {
   Serial.begin(9600);
   dht.begin();
   pinMode(triggerPin, OUTPUT);
   pinMode(echoPin, INPUT);
   WiFi.mode(WIFI_STA);
   ThingSpeak.begin(client);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
      delay(1500);
      Serial.println("Menghubungkan");
   }
   Serial.println("Terhubung");
}

void loop() {
   float humidity = dht.readHumidity();
   float temperature = dht.readTemperature();
   if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
   } else {
      Serial.println("Kelembapan: " + String(humidity));
      Serial.println("Suhu: " + String(temperature));
      ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);
      ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey);
   }

   float duration, distance;
   digitalWrite(triggerPin, LOW);
   delayMicroseconds(2);
   digitalWrite(triggerPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(triggerPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   distance = duration * 0.0344 / 2;
   Serial.println("Jarak Sensor: " + String(distance));
   ThingSpeak.writeField(myChannelNumber, 3, distance, myWriteAPIKey);
}