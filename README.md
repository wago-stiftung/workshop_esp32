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
  - 
Typischerweise meint man aber ein Entwicklungsboard, wenn man vom ESP32 spricht (SoC):
- vielseitig und schnell einsetzbar
- WLAN-Antenne, Stromversorgung des Chips und Metallstifte für die Pins sind schon vorgesehen
- unterschiedliche Boards haben auch unterschiedliche Belegungen welcher Metallstift welche Schnittstellen unterstützt ("Pin-Belegung")
Wir haben das "DOIT ESP32 DEVKIT V1" hier. Wichtig, darauf zu achten, wenn man Pin-Belegung sucht. 

_-> Ist als Bild im Repository abgelegt_

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

_-> "arduinoEsp32-1.8.13-windows-portable.zip" ist in Repository abgelegt, einfach herunterladen und entpacken_
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

Im Grunde reichen diese beiden Funktionen. Man kann natürlich auch eigene Funktionen schreiben, besonders zur Wiederverwendbarkeit und Übersichtlichkeit.
Der Aufbau ist so, wie von anderen Programmiersprachen bekannt. Kurzes Beispiel, "Zwei Zahlen addieren".

- Code wird über Pfeil-Button kompiliert und auf Board geladen. In schwarzem Balken unten steht Fortschritt und auch Fehler werden da beschrieben. 
- Beim Laden auf Board: BOOT-Taster gedrückt halten
- EN-Taster bewirkt Neustart des Boards, wenn bereits Code darauf läuft.

In den Beispielen nutzen wir Standard-Arduino Funktionen. 

_->Diese (und weitere) sind auf dem "CheatSheet" im Repository nochmal dargestellt_

### Beispiel
#### Licht steuern 
##### 1. LED anbinden
- Pin definieren und initialisieren: Funktion "pinMode(pin, mode)"
- LED wird ein- oder ausgeschaltet -> Digitales Signal (Output)
- Funktion "digitalWrite(pin, level)"
- Funktion "delay()" 

##### 2. Bewegungsmelder anbinden
- Sensor googlen: Wie wird der angebunden?
- Pin definieren und initialisieren
- Serielle Schnittstelle initialisieren: Funktion "Serial.begin(baud)"
- Sensor erkennt Bewegung oder nicht -> Digitales Signal (Input)
- Funktion "value = digitalRead(pin)"
- Wert des Sensors auf seriellem Monitor ausgeben: Funktion "Serial.println(value)"

##### 3. LED mit Bewegungsmelder steuern
- wenn Bewegung erkannt, soll LED leuchten, sonst nicht
- Schritte 1 und 2 kombinieren

#### "Heizung" steuern

Eine Heizung haben wir nicht, das ist aber einfach auch nur ein Aktor. den wir mit einer weiteren LED simulieren können.
Im Gegensatz zur LED aus 1. kann eine Heizung aber auch "ein bisschen" eingeschaltet sein. 
Bei einer LED kann man das über Dimmen umsetzen. -> Analoges Signal (Output)

##### 4. LED dimmen
- Pin definieren, __ACHTUNG: Nicht alle Pins können analoge Signale verarbeiten!__
- Es gibt eine "analogRead"-Funktion - die funktioniert aber für den ESP nicht. Wir nutzen PWM. _-> CheatSheet!_
- in Setup():
  - ledcAttachPin(pin,channel)
  - ledcSetup(channel, freq, resolution)
  <!-- 0 bis 2^(Resolution)-1 wird auf 0-3,3V Ausgang gemappt -->
- ledcWrite(channel, value)

##### 5. Temperatursensor anbinden
- Sensor googlen: Wie wird der angebunden?
- wir nutzen, laut Beispiel Bibliothken. Die müssen erst hinzugefügt werden: _Tools > Bibliotheksverwalter_
- Pin definieren und initialisieren, Serielle Schnittstelle initialisieren
- Sensor erkennt verschiedene Temperatur-Werte -> Analoges Signal (Input)
- Wir übernehmen die Konfiguration der Bibliotheken und das Auslesen des Sensors vom Beispiel-Projekt.
- Wert des Sensors auf seriellem Monitor ausgeben

##### 6. "Heizung" entsprechend der Temperatur steuern
- Schritte 4 und 5 kombinieren
- Heizung aus über definierter Temperatur, voll an unter definierter Temperatur, dazwischen "etwas an"
