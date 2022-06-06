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
String Date;
// Time For Relay
int Time_Off = 14;
int Minute_Off = 49;
int Time_On = 14;
int Minute_On = 52;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);

String formattedDate;
String dayStamp;

void setup() {

  if ( timeClient.getHours() == Time_On && timeClient.getMinutes() == Minute_On) {
    Serial.print("Relay On");
    lcd.setCursor(0, 0);
    lcd.print("Light On");
    lcd.clear();
  }
  if ( timeClient.getHours() == Time_Off && timeClient.getMinutes() == Minute_Off) {
    lcd.setCursor(0, 0);
    lcd.print("Light On");
    lcd.clear();
  }
  pinMode(relay1, OUTPUT); /*Untuk growing light */
  pinMode(relay2, OUTPUT); /* Untuk pompa mini */


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
    delay ( 5000 );
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Welcome!");
    lcd.clear();
  }

  timeClient.begin();
}


void loop() {

  // Untuk Serial Monitor
  // untuk memastiakn apakah waktu pada lcd dan serial number sama
  timeClient.update();
  //
  formattedDate = timeClient.getFormattedDate();
  Serial.println(formattedDate);
  //
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  Serial.print("DATE: ");
  Serial.println(dayStamp);
  //
  Serial.print(", ");
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

  // Testing code
  if ( timeClient.getHours() == Time_Off && timeClient.getMinutes() == Minute_Off) {
    lighton();
  }
  if ( timeClient.getHours() == Time_On && timeClient.getMinutes() == Minute_On) {
    lightoff();

  }
}


void lighton() {
  digitalWrite(relay1, HIGH);

}
void lightoff() {
  digitalWrite(relay1, LOW);
}
void screenon() {
  lcd.setCursor(9, 1);
  lcd.print("LED On");
}
void screenoff() {
  lcd.setCursor(9, 1);
  lcd.print("LED Off");
}
