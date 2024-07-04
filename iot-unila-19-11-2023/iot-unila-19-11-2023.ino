// Comment this out to disable prints and save space
// #define BLYNK_TEMPLATE_ID "TMPL6Qbt0Z5Wo"
// #define BLYNK_TEMPLATE_NAME "armas basic device"
// #define BLYNK_AUTH_TOKEN "nPt6r7yrqDvNm1wG1Bs9WGaISWxogfy1"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ARMA laptop";
char pass[] = "1234567890";

BlynkTimer timer;


// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0){
 int pinValue = param.asInt();
 digitalWrite(D0, pinValue);
}

BLYNK_WRITE(V1){
 int pinValue = param.asInt();
 digitalWrite(D1, pinValue);
}

BLYNK_WRITE(V2){
 int pinValue = param.asInt();
 digitalWrite(D2, pinValue);
}

BLYNK_WRITE(V3){
 int pinValue = param.asInt();
 digitalWrite(D3, pinValue);
}

BLYNK_WRITE(V4){
 int pinValue = param.asInt();
 digitalWrite(D4, pinValue);
}

// This function is called every time the device is connected to the Blynk.Cloud
// BLYNK_CONNECTED()
// {
//  // Change Web Link Button message to "Congratulations!"
//  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
//  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
//  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
// }


// This function sends NodeMCU uptime every second to Virtual Pin 0.
void setup()
{
 // Debug console
 Serial.begin(115200);
 Blynk.begin(auth, ssid, pass);
 pinMode(D0, OUTPUT);   // PIN DIGITAL D1
 pinMode(D1, OUTPUT);   // PIN DIGITAL D2
 pinMode(D2, OUTPUT);   // PIN DIGITAL D1
 pinMode(D3, OUTPUT);   // PIN DIGITAL D2
 pinMode(D4, OUTPUT);   // PIN DIGITAL D1
 // Setup a function to be called every second
}
void loop()
{
 Blynk.run();
 timer.run();
 // You can inject your own code or combine it with other sketches.
 // Check other examples on how to communicate with Blynk. Remember
 // to avoid delay() function!
}