#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "password.h"

AsyncWebServer server(80);

const int analogPin = 32;
const int drypin = 25;
const int moistpin = 26;

int blinkStat = false;
int analogValue = 0;

void setup() {
  //pin initialize
  pinMode(drypin, OUTPUT);
  pinMode(moistpin, OUTPUT);
  Serial.begin(115200);  // monitor display

  // http server initialize
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<!DOCTYPE html><html><head><title>ESP32 Async Web Server</title>";
    html += "<meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    html += "<style>body{font-family: Arial, sans-serif; text-align: center;} h1{color: #333;} p{font-size: 1.3em;}</style>";
    html += "</head><body>";
    html += "<h1>Hello from ESP32!</h1>";
    html += "<p>Since ESP32 started: " + String(millis() / 1000) + " [sec]</p>";
    html += "<p>Soil Moisture: " + String(analogValue) + "</p>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "404: Not found");
  });

  server.begin();
  Serial.println("HTTP async server started");
}

void toggleLED(int analogValue) {
  if (analogValue > 3500 && blinkStat == false) {
    digitalWrite(drypin, HIGH);
    blinkStat = true;
    digitalWrite(moistpin, LOW);

  } else if (analogValue > 3500 && blinkStat == true) {
    digitalWrite(drypin, LOW);
    blinkStat = false;
    digitalWrite(moistpin, LOW);

  } else {
    digitalWrite(moistpin, HIGH);
    digitalWrite(drypin, LOW);

  }
}

void loop() {
  analogValue = analogRead(analogPin);  // read analogPin
  Serial.println(analogValue);  // show analogValue (0-4095)

  toggleLED(analogValue);

  delay(1000);  // delay(ms)
}
