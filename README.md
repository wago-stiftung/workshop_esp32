# ESP32_workshop
workshop on ESP32

## Intro

### 1. Allgemein
Mikrocontroller werden in vielen Anwendungen eingesetzt, z.B. Sensorauswertung, Datenaufnahme, kleinere Berechnungen.
![image](https://user-images.githubusercontent.com/93577664/141120361-d2c95500-f700-4633-bcfd-1d05c07414c2.png)

ESP32 an sich:
- 32-bit Mikrocontroller
- relativ kleine Größe
- kostengünstig
- umfangreiche Hardware und Schnittstellen 
  - GPIOs ("General Purpose Input Output")
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

### 2. Programmierung
Anbindung an Computer über USB
- Versorgung des Boards mit 5V (für eigenständigen Betrieb über VIN-Pin)
- Austausch von Informationen im laufenden Betrieb 

Programmierung ist über verschiedene Entwicklungsplattformen zur Verfügung, z.B. Arduino IDE und MicroPython.

Arduino
- c bzw. C++ ähnliche Programmiersprache
- viele Beispiele und Bibliotheken für einfachen Einstieg

## Hands-On
### Vorbereitung
- ESP32 ist nicht standardmäßig in Arduino IDE vorhanden und muss hinzugefügt werden
*-> "arduinoEsp32-1.8.13-windows-portable.zip" ist in Repository abgelegt, einfach herunterladen und entpacken
- Board auswählen
- Verbindungsport einstellen

### Programmieren
- Einbinden von Bibliotheken
- Deklarieren von Platzhaltern
- setup() 
  - beim Hochfahren des Boards einmal aufgerufen, 
  - zur Initialisierung von Pins, Serieller Schnittstelle usw.
- loop()
  - wird wiederholt durchlaufen, solange Board eingeschaltet

Im Grunde reichen diese beiden Funktionen.
- 
