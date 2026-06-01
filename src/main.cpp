#include <Arduino.h>
#include <Wire.h>
#include <SH1106Wire.h>
#include <TinyGPSPlus.h>

// OLED
SH1106Wire display(0x3C, 8, 9);

// GPS
TinyGPSPlus gps;
HardwareSerial GPSSerial(1);

void setup() {
    Serial.begin(115200);
    
    // OLED initialisieren
    display.init();
    display.flipScreenVertically();
    display.clear();
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, "GPS Monitor");
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 20, "Warte auf GPS...");
    display.display();
    
    // GPS UART starten
    GPSSerial.begin(115200, SERIAL_8N1, 17, 18);
    
    Serial.println("GPS Monitor gestartet!");
}

void loop() {
    // GPS Daten lesen
    while (GPSSerial.available()) {
        gps.encode(GPSSerial.read());
    }
    
    // Display aktualisieren
    display.clear();
    
    // Titel
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "GPS Monitor");
    display.drawLine(0, 12, 128, 12);
    
    // Satellitenanzahl
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 15, "Sats: ");
    if (gps.satellites.isValid()) {
        display.drawString(60, 15, String(gps.satellites.value()));
    } else {
        display.drawString(60, 15, "--");
    }
    
    // Fix Status
    display.setFont(ArialMT_Plain_10);
    if (gps.location.isValid()) {
        display.drawString(0, 35, "Fix: OK ✓");
    } else {
        display.drawString(0, 35, "Fix: Warten...");
    }
    
    // HDOP
    if (gps.hdop.isValid()) {
        display.drawString(0, 48, "HDOP: " + String(gps.hdop.hdop(), 1));
    }
    
    display.display();
    delay(1000);
}