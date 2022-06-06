// Coding ini work !!!
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
char buff[10];
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char *ssid     = "Telems_Network";
const char *password = "kariso-tech";

const long utcOffsetInSeconds = 28800;
// UTC Time
// Contoh UTC+8 =8*60*60+0*60=28800
char bulan[12][12] = {"Des", "Jan", "Feb", "Mar", "Apr", "Mei", "Jun", "Jul", "Ags", "Sep", "Okt", "Nov"};
char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Wednesday", "Thursday", "Friday", "Saturday"};
int Secs;
int Minutes;
int Hours;
String myDate;
String myTime;
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);

void setup() {
  pinMode(5, OUTPUT);
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}


void loop() {
  timeClient.update();
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  ///

  Secs = timeClient.getSeconds();
  Hours = timeClient.getHours();
  Minutes = timeClient.getMinutes();
  myTime = myTime + Hours + ":" + Minutes + ":" + Secs ;
  //Print on lcd
  lcd.setCursor(0, 1);
  lcd.print(myTime);
  myTime = "";
  delay(1000);

  if ( timeClient.getHours() == 14 && timeClient.getMinutes() == 39) {
    digitalWrite(5, LOW);
    Serial.print("Relay ON");
  }
}
