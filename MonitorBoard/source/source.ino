#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Video.h>
#include <Ressources/Font6x8.h>

// WiFi Configuration
const bool AccessPointMode = false;
const char *ssid = "JioFi2_A70884";
const char *password = "tj72rcers9";

// VGA Pins
const int redPin = 15;
const int greenPin = 2;
const int bluePin = 21;
const int hsyncPin = 22;
const int vsyncPin = 23;

// Web Server
WebServer server(80);
VGA3Bit videodisplay;

// HTML Page
const char *page =
#include "page.h"
;

// Send HTML Page
void sendPage() {
    server.send(200, "text/html", page);
}

// Receive Data and Print on Serial Monitor
void text() {
    if (server.hasArg("value1") && server.hasArg("value2")) {
        String value1 = server.arg("value1");
        String value2 = server.arg("value2");

        Serial.println("--");
        Serial.print("Header: ");
        Serial.println(value1);
        Serial.print("Body: ");
        Serial.println(value2);
        Serial.println("--");

        videodisplay.println("--");
        videodisplay.print("Header: ");
        videodisplay.println(value1.c_str());
        videodisplay.print("Body: ");
        videodisplay.println(value2.c_str());
        videodisplay.println("--");

        server.send(200, "text/plain", "Data Received Successfully!");
    } else {
        server.send(400, "text/plain", "Bad Request. Missing parameters.");
    }
}

// Setup
void setup() {
    Serial.begin(115200);

    if (AccessPointMode) {
        Serial.println("Creating Access Point...");
        WiFi.softAP(ssid, password);
    } else {
        Serial.print("Connecting to SSID: ");
        Serial.println(ssid);
        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("\nWiFi Connected!");
    }

    // Initialize VGA
    videodisplay.init(VGAMode::MODE320x240, redPin, greenPin, bluePin, hsyncPin, vsyncPin);
    videodisplay.clear(videodisplay.RGBA(0, 0, 255));
    videodisplay.backColor = videodisplay.RGB(0, 0, 255);
    videodisplay.setFont(Font6x8);

    // Web Server Routes
    server.on("/", sendPage);
    server.on("/text", text);
    server.begin();

    // Display Connection Info on VGA
    videodisplay.setCursor(0, 0);
    videodisplay.println("----- VGA Terminal -----");

    if (AccessPointMode) {
        videodisplay.print("SSID: ");
        videodisplay.println(ssid);
        videodisplay.print("Password: ");
        videodisplay.println(password);
        videodisplay.println("URL: http://192.168.4.1");
    } else {
        videodisplay.print("URL: http://");
        videodisplay.println(WiFi.localIP().toString().c_str());
        Serial.print("URL: http://");
        Serial.println(WiFi.localIP().toString().c_str());
    }
    videodisplay.println("----------------------");
}

// Main Loop
void loop() {
    server.handleClient();
    delay(10);
}