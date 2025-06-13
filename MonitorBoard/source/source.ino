#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Video.h>
#include <Ressources/Font6x8.h>

// WiFi Configuration
const char *ssid = "WIFI_SSID";   // Replace with your Wi-Fi SSID
const char *password = "WIFI_PASSWORD";  // Replace with your Wi-Fi Password

// VGA Pins
const int redPin = 15;
const int greenPin = 2;
const int bluePin = 21;
const int hsyncPin = 22;
const int vsyncPin = 23;

// Web Server and VGA Display
WebServer server(80);
VGA3Bit videodisplay;

// HTML Page (served from external header file)
const char *page =
#include "page.h"
  ;

// Send HTML Page
void sendPage() {
  server.send(200, "text/html", page);
}

// Receive Data and Print to Serial and VGA
void text() {
    if (server.hasArg("value1") && server.hasArg("value2")) {
        String value1 = server.arg("value1");
        String value2 = server.arg("value2");

        value1.trim();
        value2.trim();

        if (value1.length() == 0 && value2.length() == 0) {
            server.send(400, "text/plain", "Bad Request. Empty parameters.");
            return;
        }

        Serial.println("--");
        Serial.print("Header: ");
        Serial.println(value1);
        Serial.print("Body: ");
        Serial.println(value2);
        Serial.println("--");

        // Clear screen
        videodisplay.clear(videodisplay.RGBA(0, 0, 255));

        // Constants
        const int screenWidth = 320;
        const int screenHeight = 240;
        const int charWidth = 6;
        const int charHeight = 8;
        const int lineSpacing = 4;
        const int maxCharsPerLine = screenWidth / charWidth;

        // Prepare lines
        String lines[10]; // supports up to 10 wrapped lines
        int lineCount = 0;

        // Add horizontal divider
        String divider = String('-');
        while (divider.length() < maxCharsPerLine) divider += '-';
        lines[lineCount++] = divider;

        // Helper lambda to wrap text
        auto wrapText = [&](String text) {
            while (text.length() > 0) {
                String segment = text.substring(0, maxCharsPerLine);
                lines[lineCount++] = segment;
                text = text.substring(segment.length());
            }
        };

        wrapText(value1);
        lines[lineCount++] = divider;
        wrapText(value2);

        // Draw lines from fixed top Y position
        int startY = 20;  // Top margin
        for (int i = 0; i < lineCount; i++) {
            int x = (screenWidth - lines[i].length() * charWidth) / 2;
            int y = startY + i * (charHeight + lineSpacing);
            videodisplay.setCursor(x, y);
            videodisplay.print(lines[i].c_str());
        }

        server.send(200, "text/plain", "Data Received Successfully!");
    } else {
        server.send(400, "text/plain", "Bad Request. Missing parameters.");
    }
}



// Setup
void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  // Initialize VGA
  videodisplay.init(VGAMode::MODE320x240, redPin, greenPin, bluePin, hsyncPin, vsyncPin);
  videodisplay.clear(videodisplay.RGBA(0, 0, 255));
  videodisplay.backColor = videodisplay.RGB(0, 0, 255);
  videodisplay.setFont(Font6x8);

  // Web Server Routes
  server.on("/", sendPage);
  server.on("/text", text);
  server.begin();

  // --- Centered Display ---
  const int screenWidth = 320;
  const int charWidth = 6;
  const int lineHeight = 10;

  String title = "----- MonitorBoard -----";
  String url = "URL: http://" + WiFi.localIP().toString();
  String divider = "------------------------";

  int titleX = (screenWidth - title.length() * charWidth) / 2;
  int urlX = (screenWidth - url.length() * charWidth) / 2;
  int dividerX = (screenWidth - divider.length() * charWidth) / 2;

  videodisplay.setCursor(titleX, 100);
  videodisplay.println(title.c_str());

  videodisplay.setCursor(urlX, 110 + lineHeight);
  videodisplay.println(url.c_str());

  videodisplay.setCursor(dividerX, 110 + 2 * lineHeight);
  videodisplay.println(divider.c_str());

  Serial.print("URL: http://");
  Serial.println(WiFi.localIP().toString().c_str());
}


// Main Loop
void loop() {
  server.handleClient();
  delay(10);
}
