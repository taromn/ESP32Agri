#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "password.h"

AsyncWebServer server(80);

// if needed, change these pins to your own pin numbers
const int analogPin = 32;  // sensor pin
const int drypin = 25;  // LED pin that blinks when soil is dry
const int moistpin = 26;  // LED pin that blinks when soil is moist

int blinkStat = false;
int analogValue = 0;

void setup() {
  //pin initialize
  pinMode(drypin, OUTPUT);
  pinMode(moistpin, OUTPUT);
  Serial.begin(115200);  // monitor display

  // Initialize LittleFS
  if(!LittleFS.begin(true)){
    Serial.println("LittleFS Mount Failed");
    return;
  }
  Serial.println("LittleFS mounted successfully");

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

  server.serveStatic("/", LittleFS, "/");

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request){
    String textColor = (analogValue <= 3400) ? "blue" : "red";
    String html = "<!DOCTYPE html><html><head><title>ESP32 Async Web Server</title>";
    html += "<meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    html += "<style>body{font-family: Arial, sans-serif; text-align: center;} h1{color: #333;} p{font-size: 1.3em;}</style>";
    html += "</head><body>";
    html += "<h1>Hello from ESP32!</h1>";
    html += "<p>Since ESP32 started: " + String(millis() / 1000) + " [sec]</p>";
    html += "<p>Soil Moisture: <span style=\"color: " + textColor + ";\">" + String(analogValue) + "</span></p>";
    html += "<img src=\"good_pot.png\" alt=\"Good Pot\" style=\"max-width: 100px; height: auto;\">";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/metrics", HTTP_GET, [](AsyncWebServerRequest *request){
    String metrics = "# HELP moisture_raw Soil moisture value (0-4095)\n";
    metrics += "# TYPE moisture_raw gauge\n";
    metrics += "moisture_raw " + String(analogValue) + "\n";
    metrics += "# HELP uptime_seconds ESP32 uptime in seconds\n";
    metrics += "# TYPE uptime_seconds counter\n";
    metrics += "uptime_seconds " + String(millis() / 1000) + "\n";
    request->send(200, "text/plain", metrics);
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "404: Not found");
  });

  server.begin();
  Serial.println("HTTP async server started");
}

void toggleLED(int analogValue) {
  if (analogValue > 3400 && blinkStat == false) {
    digitalWrite(drypin, HIGH);
    blinkStat = true;
    digitalWrite(moistpin, LOW);

  } else if (analogValue > 3400 && blinkStat == true) {
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
