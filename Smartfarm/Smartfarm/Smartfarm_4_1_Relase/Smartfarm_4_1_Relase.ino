// Arduino libary
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
// Perhatian !
// Untuk nodemcu  pin 4 = D4
// SCL=D1
// SDA=D2
// relay define
#define relay1 D4
#define relay2 D3

char buff[10];
// Untuk LCD 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Nama SSID dan password Wi-fi 
const char *ssid     = "Telems_Network";
const char *password = "kariso-tech";

const long utcOffsetInSeconds = 28800;
// UTC Time
// Contoh UTC+8 =8*60*60+0*60=28800

// Untuk waktu 
int Secs;
int Minutes;
int Hours;
String myDate;
String myTime;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);

void setup() {
  pinMode(relay1, OUTPUT); /*Untuk growing light */
  pinMode(relay2, OUTPUT); /* Untuk pompa mini */

  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    lcd.setCursor(0, 0);
    lcd.print("Conncet To");
    lcd.setCursor(0, 1);
    lcd.print(ssid);
    delay ( 2000 );
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Internet OK");
    delay ( 5000 );
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Welcome!");

  }

  timeClient.begin();
}


void loop() {

  // Untuk Serial Monitor
  // untuk memastiakn apakah waktu pada lcd dan serial number sama
  timeClient.update();
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  ///
  {
    Secs = timeClient.getSeconds();
    Hours = timeClient.getHours();
    Minutes = timeClient.getMinutes();
    myTime = myTime + Hours + ":" + Minutes + ":" + Secs ;
    //Print on lcd
    lcd.setCursor(0, 1);
    lcd.print(myTime);
    myTime = "";
    delay(1000);
  }

// Testing code 
  if ( timeClient.getHours() == 16 && timeClient.getMinutes() == 5) {
    Serial.print("Relay ON");
    digitalWrite(relay1, HIGH); //Pump 1 On

    if ( timeClient.getHours() == 16 && timeClient.getMinutes() == 10) {
      Serial.print("Relay ON");
      digitalWrite(relay1, LOW); //Pump 1 On
    }
  }
}
