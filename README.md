# ESP32_workshop
workshop on ESP32

## Intro
Mikrocontroller werden in vielen Anwendungen eingesetzt, z.B. Sensorauswertung, Datenaufnahme, kleinere Berechnungen.
![image](https://user-images.githubusercontent.com/93577664/141120361-d2c95500-f700-4633-bcfd-1d05c07414c2.png)
ESP32 an sich:
- 32-bit Mikrocontroller
- 240 MHz
- relativ kleine Größe
- kostengünstig
- umfangreiche Hardware und Schnittstellen 
  - GPIOs
  - I2C
  - Ethernet
  - WLAN
  - Bluetooth
  - ...
Typischerweise meint man aber ein Entwicklungsboard, wenn man vom ESP32 spricht (SoC):
- vielseitig und schnell einsetzbar
- WLAN-Antenne, Stromversorgung des Chips und Metallstifte für die Pins sind schon vorgesehen
- unterschiedliche Boards haben auch unterschiedliche Belegungen welcher Metallstift welche Schnittstellen unterstützt ("Pin-Belegung")
Wir haben das "DOIT ESP32 DEVKIT V1" hier. Wichtig, darauf zu achten, wenn man Pin-Belegung sucht. 
*-> Ist als Bild im Repository abgelegt *

## Programmieren
