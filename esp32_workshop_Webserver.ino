#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include <WiFi.h>
#include <WebServer.h>

#define BMP_SDA 21
#define BMP_SCL 22

Adafruit_BMP280 bmp; //I2C

#define LED_rot 32
#define LED_gruen 33

/* Put your SSID & Password */
const char* ssid = "ESP32";  // Enter SSID here
const char* password = "012345678";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);

bool LED_rot_status = LOW;
bool LED_gruen_status = LOW;

float Temperature;
float Pressure;
uint8_t i = 200;

void setup ()
{
  // Initialisierung Ausgangspins für die LEDs
  pinMode (LED_rot, OUTPUT);
  pinMode (LED_gruen, OUTPUT);

  // Initialisierung Serieller Monitor
  Serial.begin(9600);

  // Initialisierung BPM280 mit Ausgabe ob erfolgreich auf Monitor
  Serial.println(F("BMP280 test"));
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }


  // Initialisierung Webserver
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", handle_OnConnect);
  server.on("/led_rot_on", handle_led_rot_on);
  server.on("/led_rot_off", handle_led_rot_off);
  server.on("/led_gruen_on", handle_led_gruen_on);
  server.on("/led_gruen_off", handle_led_gruen_off);
  server.onNotFound(handle_NotFound);

  server.begin();
}

void loop () //Hauptprogrammschleife
{
  // -----------------------------------------------------------------
  // LED Modul
  // -----------------------------------------------------------------
  //  digitalWrite (LED_rot, HIGH); // LED wird eingeschaltet
  //  digitalWrite (LED_gruen, LOW); // LED wird eingeschaltet
  //  delay (3000); // Wartemodus für 3 Sekunden
  //
  //  digitalWrite (LED_rot, LOW); // LED wird eingeschaltet
  //  digitalWrite (LED_gruen, HIGH); // LED wird eingeschaltet
  //  delay (3000); // Wartemodus für weitere zwei Sekunden in denen die LEDs dann umgeschaltet sind


  // -----------------------------------------------------------------
  // BMP280
  // -----------------------------------------------------------------
  //  Serial.print(F("Temperature = "));
  //  Serial.print(bmp.readTemperature());
  //  Serial.println(" °C");
  //
  //  Serial.print(F("Pressure = "));
  //  Serial.print(bmp.readPressure()/100);
  //  Serial.println(" hPa");
  //
  //  Serial.print(F("Approx altitude = "));
  // // Serial.print(bmp.readAltitude(1013.25)); // this should be adjusted to your local forcase
  //  Serial.print(bmp.readAltitude(1017.9));
  //  Serial.println(" m");
  //
  //  Serial.println();
  //  delay(2000);

  // -----------------------------------------------------------------
  // Webserver zum Schalten der LEDs und Anzeigen der Messwerte
  // -----------------------------------------------------------------
  server.handleClient();

  if (LED_rot_status)
  {
    if (!LED_gruen_status) {
      digitalWrite(LED_rot, HIGH);
    }
  }
  else
  {
    digitalWrite(LED_rot, LOW);
  }

  if (LED_gruen_status)
  {
    if (!LED_rot_status) {
      digitalWrite(LED_gruen, HIGH);
    }
  }
  else
  {
    digitalWrite(LED_gruen, LOW);
  }

  if (i > 200) {
    Temperature = bmp.readTemperature();
    Pressure    = bmp.readPressure() / 100;
    i = 0;
  }
  else {
    i++;
  }

}

void handle_OnConnect() {
  LED_rot_status = LOW;
  LED_gruen_status = LOW;
  Temperature = 0.0;
  Pressure = 0.0;

  Serial.println("GPIO4 Status: OFF | GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(LED_rot_status, LED_gruen_status, Temperature, Pressure));
}

void handle_led_rot_on() {
  LED_rot_status = HIGH;
  Serial.println("GPIO4 Status: ON");
  server.send(200, "text/html", SendHTML(true, LED_gruen_status, Temperature, Pressure));
}

void handle_led_rot_off() {
  LED_rot_status = LOW;
  Serial.println("GPIO4 Status: OFF");
  server.send(200, "text/html", SendHTML(false, LED_gruen_status, Temperature, Pressure));
}

void handle_led_gruen_on() {
  LED_gruen_status = HIGH;
  Serial.println("GPIO5 Status: ON");
  server.send(200, "text/html", SendHTML(LED_rot_status, true, Temperature, Pressure));
}

void handle_led_gruen_off() {
  LED_gruen_status = LOW;
  Serial.println("GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(LED_rot_status, false, Temperature, Pressure));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led_rot_stat, uint8_t led_gruen_stat, float temp, float pres) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESP32 Web Server</h1>\n";
  ptr += "<h3>Using Access Point(AP) Mode</h3>\n";

  if (led_rot_stat)
  {
    ptr += "<p>LED Rot Status: ON</p><a class=\"button button-off\" href=\"/led_rot_off\">OFF</a>\n";
  }
  else
  {
    ptr += "<p>LED Rot Status: OFF</p><a class=\"button button-on\" href=\"/led_rot_on\">ON</a>\n";
  }

  if (led_gruen_stat)
  {
    ptr += "<p>LED Gruen Status: ON</p><a class=\"button button-off\" href=\"/led_gruen_off\">OFF</a>\n";
  }
  else
  {
    ptr += "<p>LED Gruen Status: OFF</p><a class=\"button button-on\" href=\"/led_gruen_on\">ON</a>\n";
  }

  ptr += "<p>Temperature: </p>" + String((int)temp) + "*C\n";

  ptr += "<p>Pressure: </p>" + String((int)pres) + "hPa\n";

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;

}
