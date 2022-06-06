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
#define buzzer D5
#define relay3 D6
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
String myTime;
String Date;
// Time For Relay
int Time_Off = 13;
int Minute_Off = 24;
int Time_On = 13;
int Minute_On = 25;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);

String formattedDate;
String dayStamp;

void setup() {

  pinMode(relay1, OUTPUT); /*Untuk growing light */
  pinMode(relay2, OUTPUT); /* Untuk pompa mini */
  pinMode(relay3, OUTPUT); /* Untuk pompa mini */
  pinMode(buzzer, OUTPUT);
  
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    lcd.setCursor(0, 0);
    lcd.print("Connect To");
    lcd.setCursor(0, 1);
    lcd.print(ssid);
    delay ( 2000 );
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Internet OK");
    delay ( 3000 );
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Welcome!");
    lcd.clear();
  }

  timeClient.begin();
}


void loop() {
  timeClient.update();
  lcd_time();
  opration();
}
void opration() {
  if ( timeClient.getHours() == Time_Off && timeClient.getMinutes() == Minute_Off) {
    lighton();
  }
  if ( timeClient.getHours() == Time_On && timeClient.getMinutes() == Minute_On) {
    lightoff();
  }
}

void lcd_time() {
  Secs = timeClient.getSeconds();
  Hours = timeClient.getHours();
  Minutes = timeClient.getMinutes();
  Date = dayStamp;
  myTime =  myTime + Hours + ":" + Minutes + ":" + Secs ;
  //Print on lcd
  lcd.setCursor(0, 1);
  lcd.print(myTime);
  myTime = "";
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print(Date);
}
// Untuk menyalakan lampu.
void lighton() {
  digitalWrite(relay1, HIGH);
}
// Untuk mematikan lampu.
void lightoff() {
  digitalWrite(relay1, LOW);
}
// Untuk tone buzzer.
void Tone() {
  tone(buzzer, 700);
  delay(1000);
  noTone(buzzer);
}
// Untuk menyalakan pompa.
void pump() {
  digitalWrite(relay3, LOW);
  delay(3000);
  digitalWrite(relay3, HIGH);
}
