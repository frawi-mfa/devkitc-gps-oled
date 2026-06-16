# DevKitC GPS Monitor mit OLED

Mobiler GPS Monitor auf Basis des ESP32-S3 DevKitC-1 N16R8 mit 1.3" OLED Display.
Entwickelt für den Einsatz beim FPV Drohnenfliegen — Cold Fix abwarten ohne die 
Drohne einschalten zu müssen.

## Hardware

| Komponente | Details |
|---|---|
| **Board** | RUIZHI ESP32-S3 DevKitC-1 N16R8 (16MB Flash, 8MB PSRAM) |
| **Display** | 1.3" OLED SH1106, 128×64 Pixel, I2C |
| **GPS** | Flywoo Goku GM10 Nano V3.1 (u-blox M10) |
| **Erweiterung** | ESP32-S3 GPIO Extension Board |

## Verkabelung

### OLED (I2C)
OLED VCC → 3.3V
OLED GND → GND
OLED SDA → GPIO8
OLED SCL → GPIO9

### GPS (UART)
GPS VCC → 3.3V
GPS GND → GND
GPS TX  → GPIO17 (RX)
GPS RX  → GPIO18 (TX) optional

## Software

- **Framework:** Arduino (PlatformIO)
- **Board:** esp32-s3-devkitc-1
- **Libraries:**
  - ThingPulse ESP8266 and ESP32 OLED driver (SH1106Wire)
  - TinyGPSPlus

## Wichtige Hinweise

- GPS Baudrate: **115200**
- GPIO43/44 (Standard UART) nicht verwenden — intern mit CH343P belegt!
- OLED I2C Adresse: `0x3C`

## Anzeige

Das OLED zeigt live:
- 🛰️ Satellitenanzahl
- ✅ Fix Status (OK / Warten...)
- 📡 HDOP Wert (Genauigkeit)

## Typische Werte im Freien

| Wert | Bedeutung |
|---|---|
| Sats < 5 | Kein zuverlässiger Fix |
| Sats 6-8 | Guter Fix |
| Sats > 10 | Sehr guter Fix |
| HDOP < 1.0 | Ausgezeichnete Genauigkeit |
| HDOP < 2.0 | Gute Genauigkeit |

## Geplante Erweiterungen

- Koordinaten anzeigen
- Uhrzeit aus GPS
- BLE Übertragung ans Waveshare Dashboard
- Version mit 2.4" TFT + SD Karten Logging

## Projektkontext

Teil eines größeren ESP32 Projektnetzwerks:
- **[waveshare-esp32s3-dashboard](https://github.com/frawi-mfa/waveshare-esp32s3-dashboard)** — Zentrales Netzwerk Dashboard
- **[esp32c3-bme280-ble](https://github.com/frawi-mfa/esp32c3-bme280-ble)** — Wetterstation Node
