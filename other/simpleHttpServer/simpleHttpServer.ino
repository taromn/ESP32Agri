#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "";
const char* password = "";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

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
    html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    html += "<style>body{font-family: Arial, sans-serif; text-align: center;} h1{color: #333;} p{font-size: 1.2em;}</style>";
    html += "</head><body>";
    html += "<h1>Hello from ESP32! (Async)</h1>";
    html += "<p>ESP32が起動してからの時間: " + String(millis() / 1000) + " 秒</p>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/plain", "404: Not found");
  });

  server.begin();
  Serial.println("HTTP async server started");
}

void loop() {
}