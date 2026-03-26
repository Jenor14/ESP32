#include <WiFi.h>
#include <WebServer.h>

// WLAN-Zugangsdaten für den ESP32 als Access Point
const char* ssid = "ESP32-LED-AP";
const char* password = "12345678";

// LED Pin
const int ledPin = 2;

// Webserver auf Port 80
WebServer server(80);

void handleRoot() {
  // HTML-Seite mit LED-Steuerung
  String html = "<html><body>";
  html += "<h1>ESP32 LED Steuerung</h1>";
  html += "<p><a href=\"/on\"><button>LED AN</button></a></p>";
  html += "<p><a href=\"/off\"><button>LED AUS</button></a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleLEDOn() {
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleLEDOff() {
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // ESP32 als Access Point starten
  WiFi.softAP(ssid, password);
  Serial.println("Access Point gestartet!");
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.softAPIP());

  // Webserver Routen
  server.on("/", handleRoot);
  server.on("/on", handleLEDOn);
  server.on("/off", handleLEDOff);

  server.begin();
  Serial.println("Webserver gestartet!");
}

void loop() {
  server.handleClient();
}
