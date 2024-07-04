#include <ESP8266WiFi.h>
#include "CTBot.h"

CTBot robot;
#define relayPin D2

const char* ssid_wifi = "ARMA laptop";
const char* password = "1234567890";
const char* api_token = "6801521854:AAGZ4PKGkC7Bgxs_AJlVOgbpdDawf_QD9y0";

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  // Koneksi ke Wi-Fi
  WiFi.begin(ssid_wifi, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Koneksi ke Telegram
  robot.setTelegramToken(api_token);
  
  // Periksa koneksi Telegram
  if(robot.testConnection())
    Serial.println("Terhubung :)");
  else
    Serial.println("Error!");
}

void loop() {
  TBMessage message;

  if(robot.getNewMessage(message)) {
    Serial.print("Ada pesan Masuk: ");
    Serial.println(message.text);     
    
    if(message.text.equalsIgnoreCase("ON")) {
      digitalWrite(relayPin, LOW);
      robot.sendMessage(message.sender.id, "Lampu Menyala");
    } else if(message.text.equalsIgnoreCase("OFF")) {
      digitalWrite(relayPin, HIGH);
      robot.sendMessage(message.sender.id, "Lampu Mati");   
    } else {
      String reply = "Perintah salah. Coba kirim ON atau OFF!";
      robot.sendMessage(message.sender.id, reply);
    }
  }
}
