// Platzhalter für Pin-Belegung
#define LED 5
#define BEWEGUNGSSENSOR 33
#define HEIZUNG 4
#define ABSTANDSSENSOR_Trig 25
#define ABSTANDSSENSOR_Echo 26

// Variablen PWM
const int PWM_channel = 0;
const int PWM_freq = 5000;
const int PWM_resolution = 8;
const int maximum = (2 ^ PWM_resolution) - 1;

// Variablen Abstand
int maximumRange = 300;
int minimumRange = 2;
long abstand;
long dauer;


// Setup-Funktion, wird einmal durchlaufen zur Initialisierung
void setup()
{
  // Schritt 1
  pinMode(LED, OUTPUT);

  // Schritt 2
  pinMode(BEWEGUNGSSENSOR, INPUT);
  Serial.begin(9600);

  // Schritt 4
  ledcSetup(PWM_channel, PWM_freq, PWM_resolution);   // LED PWM Funktionalitäten konfigurieren
  ledcAttachPin(HEIZUNG, PWM_channel);                // Konfigurierten PWM Kanal an GPIO anhängen

  // Schritt 5
  pinMode(ABSTANDSSENSOR_Trig, OUTPUT);
  pinMode(ABSTANDSSENSOR_Echo, INPUT);

}


// wird während der Laufzeit immerwieder durchlaufen
void loop()
{
  ____________________________________________________________________
  // Schritt 1 - LED schalten, digitaler Output
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);

  //____________________________________________________________________
  // Schritt 2 - Bewegung erkennen, digitaler Input
  bool bewegung = digitalRead (BEWEGUNGSSENSOR);
  // Wenn der Wert des Digital_Eingang 1 entspricht,
  // ist eine Bewegung erkannt und dies wird als Meldung ausgegeben
  if (bewegung == true)
  {
    Serial.println ("Bewegung erkannt");
  }
  delay (200);

  //____________________________________________________________________
  // Schritt 3 - LED abhängig von Bewegung schalten
  bool bewegung = digitalRead (BEWEGUNGSSENSOR);
  // wenn Bewegungssensor
  //if (bewegung == true)
  // wenn Linienfinder
  if (bewegung == false)
  {
    Serial.println ("Bewegung erkannt");
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
  delay (200);

  //____________________________________________________________________
  // Schritt 4 - LED dimmen, analoger Output / PWM
  // Helligkeit erhöhen
  for (int i = 0; i <= maximum; i++)
  {
    ledcWrite(PWM_channel, i);
    delay(25);
  }
  // Helligkeit verringern
  for (int i = 255; i >= 0; i--)
  {
    ledcWrite(PWM_channel, i);
    delay(25);
  }

  //____________________________________________________________________
  // Schritt 5 - Abstand messen, analoger Input
  // Abstandsmessung wird mittels des 10us langen Triggersignals gestartet
  digitalWrite(ABSTANDSSENSOR_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ABSTANDSSENSOR_Trig, LOW);

  // Nun wird am Echo-Eingang gewartet, bis das Signal aktiviert wurde
  // und danach die Zeit gemessen, wie lang es aktiviert bleibt
  dauer = pulseIn(ABSTANDSSENSOR_Echo, HIGH);

  // Nun wird der Abstand mittels der aufgenommenen Zeit berechnet
  abstand = dauer / 58.2;
  // Überprüfung ob gemessener Wert innerhalb der zulässingen Entfernung liegt
  if (abstand >= maximumRange || abstand <= minimumRange) {
    // Falls nicht wird eine Fehlermeldung ausgegeben.
    Serial.println("Abstand ausserhalb des Messbereichs");
    Serial.println("-----------------------------------");
  }

  else {
    // Der berechnete Abstand wird in der seriellen Ausgabe ausgegeben
    Serial.print("Der Abstand betraegt:");
    Serial.print(abstand);
    Serial.println("cm");
    Serial.println("-----------------------------------");
  }
  // Pause zwischen den einzelnen Messungen
  delay(500);


  //____________________________________________________________________
  // Schritt 6 - LED abhängig von Temperatur schalten
  digitalWrite(ABSTANDSSENSOR_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ABSTANDSSENSOR_Trig, LOW);

  // Nun wird am Echo-Eingang gewartet, bis das Signal aktiviert wurde
  // und danach die Zeit gemessen, wie lang es aktiviert bleibt
  dauer = pulseIn(ABSTANDSSENSOR_Echo, HIGH);

  // Nun wird der Abstand mittels der aufgenommenen Zeit berechnet
  abstand = dauer / 58.2;

  if (abstand < 5) {
    ledcWrite(PWM_channel, 0);
  }
  else if (abstand < 10) {
    ledcWrite(PWM_channel, 0.2 * maximum);
  }
  else if (abstand < 20) {
    ledcWrite(PWM_channel, 0.4 * maximum);
  }
  else if (abstand < 30) {
    ledcWrite(PWM_channel, 0.6 * maximum);
  }
  else if (abstand < 40) {
    ledcWrite(PWM_channel, 0.8 * maximum);
  }
  else {
    ledcWrite(PWM_channel, maximum);
  }

}
