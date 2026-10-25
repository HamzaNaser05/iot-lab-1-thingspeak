# ESP32 to ThingSpeak IoT Telemetry

## Student Information
- **Name:** Hamza Nasser
- **University ID:** 12324183

## Project Overview
This project connects an ESP32 microcontroller to Wi-Fi and reads real-time temperature and humidity data from a DHT22 sensor. The telemetry data, along with the student identifier, is transmitted to ThingSpeak every 20 seconds using the official ThingSpeak IoT library.

## Project Links
- **ThingSpeak Public Channel:** https://thingspeak.com/channels/3549775
- **Wokwi Project:** [https://wokwi.com/projects/478888917864882177]

## Hardware & Wiring
| Sensor (DHT22) | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DATA / SDA | GPIO 15 |

## Screenshots
### ThingSpeak Dashboard & Live Charts
![ThingSpeak Dashboard](screenshots/thingspeak_channel.png)

### Serial Monitor Output
![Serial Monitor](screenshots/serial_monitor.png)
