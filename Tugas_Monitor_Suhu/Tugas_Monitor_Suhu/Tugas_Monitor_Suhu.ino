#define BLYNK_TEMPLATE_ID "TMPL61AWu3azS"
#define BLYNK_TEMPLATE_NAME "DHT device"
#define BLYNK_AUTH_TOKEN "A7um68amYCDUzqfEPJa5EEbUnZw0Vf94"
#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <ESP8266WiFi.h>

char auth[] = BLYNK_AUTH_TOKEN;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ARMA laptop";
char pass[] = "1234567890";

#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
int led1 = D0;
int led2 = D1;

void setup() {
   Serial.begin(115200);
   Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
   dht.begin();
   pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);
   timer.setInterval(1000L, sendSensor);
}

void loop() {
   Blynk.run();
   timer.run();
}

void sendSensor() {
   float humidity = dht.readHumidity();
   float temperature = dht.readTemperature();
   if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
   }
   Blynk.virtualWrite(V3, temperature);
   Blynk.virtualWrite(V2, humidity);

   Serial.print("Temperature : ");
   Serial.print(temperature);
   Serial.print("|| Humidity : ");
   Serial.println(humidity);

   if (humidity < 45) {
      Blynk.virtualWrite(V0, "Too dry");
      digitalWrite(led1, HIGH);
   } else if (humidity > 65) {
      Blynk.virtualWrite(V0, "Too humid");
      digitalWrite(led1, HIGH);
   } else {
      Blynk.virtualWrite(V0, "Normal");
      digitalWrite(led1, LOW);
   }
   if (temperature < 22) {
      Blynk.virtualWrite(V1, "Too cold");
      digitalWrite(led2, HIGH);
   } else if (temperature > 35) {
      Blynk.virtualWrite(V1, "Too hot");
      digitalWrite(led2, HIGH);
   } else {
      Blynk.virtualWrite(V1, "Normal");
      digitalWrite(led2, LOW);
   }

   if (temperature > 35) {
      // Blynk.email("abc@gmail.com", "Alert", "Temperature over 30C!");
      Blynk.logEvent("Notification",
                     "The temperature conditions in the room are abnormal.");
   }
}