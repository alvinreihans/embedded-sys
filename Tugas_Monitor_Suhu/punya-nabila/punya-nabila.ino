#define BLYNK_TEMPLATE_ID "TMPL61AWu3azS"
#define BLYNK_TEMPLATE_NAME "DHT device"
#define BLYNK_AUTH_TOKEN "A7um68amYCDUzqfEPJa5EEbUnZw0Vf94"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 

#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ARMA laptop";
char pass[] = "1234567890";

#define DHTPIN D2          // Mention the digital pin where you connected 
#define DHTTYPE DHT11     // DHT 11  
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;



void setup(){
   Serial.begin(115200);
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}
void sendSensor(){
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V7, t);
  Blynk.virtualWrite(V8, h);
  
  Serial.print("Suhu : ");
  Serial.print(t);
  Serial.print("|| Kelembapan : ");
  Serial.println(h);

  if(h > 68) {
    Blynk.virtualWrite(V3, "Kelembapan tidak normal");
  } else {
    Blynk.virtualWrite(V3, "Kelembapan normal");
  }
  if(t > 31){
    //Blynk.email("abc@gmail.com", "Alert", "Temperature over 30C!");
    Blynk.virtualWrite(V2, "Panas Banget");
  } else {
    Blynk.virtualWrite(V2, "Suhu normal");
  }


  if(t > 30){
    //Blynk.email("abc@gmail.com", "Alert", "Temperature over 30C!");
    Blynk.logEvent("notifikasi","Suhu diatas 30 Derajat celcius");
  }
}