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

_-> Ist als Bild im Repository abgelegt_

### 2. Programmierung - Grundlagen
Anbindung an Computer über USB
- Versorgung des Boards mit 5V (für eigenständigen Betrieb über VIN-Pin) 
__ACHTUNG: Der eigentliche ESP arbeitet intern mit 3,3 V! Darauf achten, wenn man Sensoren anschließt!__
- Austausch von Informationen im laufenden Betrieb 

Programmierung ist über verschiedene Entwicklungsplattformen zur Verfügung, z.B. Arduino IDE und MicroPython.

Arduino
- C bzw. C++ ähnliche Programmiersprache
- viele Beispiele und Bibliotheken für einfachen Einstieg

## Hands-On
### Vorbereitung
- ESP32 ist nicht standardmäßig in Arduino IDE vorhanden und muss hinzugefügt werden
- Board auswählen
- Verbindungsport einstellen

### Programmieren
- setup() 
  - beim Hochfahren des Boards einmal aufgerufen, 
  - zur Initialisierung von Pins, Serieller Schnittstelle usw.
- loop()
  - wird wiederholt durchlaufen, solange Board eingeschaltet

- Code wird über Pfeil-Button kompiliert und auf Board geladen. In schwarzem Balken unten steht Fortschritt und auch Fehler werden da beschrieben. 
- Beim Laden auf Board: BOOT-Taster gedrückt halten
- EN-Taster bewirkt Neustart des Boards, wenn bereits Code darauf läuft.

In den Beispielen nutzen wir Standard-Arduino Funktionen. 

_->Diese (und weitere) sind auf dem "CheatSheet" im Repository nochmal dargestellt_

### Beispiel
#### Licht steuern 
##### 1. LED anbinden
- Pin über Platzhalter definieren und in Setup initialisieren: Funktion "pinMode(pin, mode)"
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

##### 5. Abstandssensor anbinden
- Sensor googlen: Wie wird der angebunden? (z.B. über "Nützliche Links")
- Pin definieren und initialisieren, Serielle Schnittstelle initialisieren
- Sensor erkennt verschiedene über Ultraschall Abstand -> Analoges Signal (Input)
- Wert des Sensors auf seriellem Monitor ausgeben

##### 6. "Heizung" entsprechend des Abstands steuern
- Schritte 4 und 5 können natürlich auch kombiniert werden
- Heizung aus über definierter Temperatur, voll an unter definierter Temperatur, dazwischen "etwas an"
