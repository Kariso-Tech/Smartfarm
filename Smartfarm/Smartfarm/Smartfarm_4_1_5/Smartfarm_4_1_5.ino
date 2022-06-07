// Arduino libary
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <RTClib.h>
//
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Perhatian !
// Untuk nodemcu  pin 4 = D4
// SCL=D1
// SDA=D2
// relay define
#define relay1 D3
#define relay2 D4
#define buzzer D5
#define relay3 D6
char buff[10];
// Untuk LCD 16x2

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
// Date
String Date;
String formattedDate;
String dayStamp;
// Time For Relay
int Time_Off = 16;
int Minute_Off = 4;
int Time_On = 16;
int Minute_On = 8;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  pinMode(relay1, OUTPUT); /*Untuk growing light */
  pinMode(relay2, OUTPUT); /* Untuk pompa mini */
  pinMode(relay3, OUTPUT); /* Untuk pompa mini */
  pinMode(buzzer, OUTPUT); /*Untuk Buzzer */
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, -0); //Max (x,y) y= -0 sampai 25
    display.println("System Booting......");
    display.display();
    display.clearDisplay();
    delay(3000);
    display.setCursor(0, -0); //Max (x,y) y= -0 sampai 25
    display.println("Connect To");
    display.display();
    display.clearDisplay();
    delay(2000);
    display.setCursor(0, -0); //Max (x,y) y= -0 sampai 25
    display.println(ssid);
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setCursor(0, -0);
    display.println("Internet  Ok");
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setCursor(0, -0);
    display.println("Welcome To SF-4.1.5");
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setCursor(0, -0);
    display.println("Desgin By Telems");
    display.display();
    delay(3000);
    display.clearDisplay();

  }
  timeClient.begin();

}
void loop() {
  timeClient.update();
  on_notif();
  off_notif();
  opration();
  lcdtime();
  alaram_1();
  alaram_2();

}
void opration() {
  if ( timeClient.getHours() == Time_Off && timeClient.getMinutes() == Minute_Off) {
    lighton();
  }
  if ( timeClient.getHours() == Time_On && timeClient.getMinutes() == Minute_On) {
    lightoff();
  }
}

void oled_on_screen() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 8);
  display.println("LED ON");
  display.display();
  delay(2000);
}
void oled_off_screen() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, -8);
  display.println("LED OFF");
  display.display();

}

void lcdtime() {

  formattedDate = timeClient.getFormattedDate();
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  //
  Secs = timeClient.getSeconds();
  Hours = timeClient.getHours();
  Minutes = timeClient.getMinutes();
  myTime =  myTime + Hours + ":" + Minutes + ":" + Secs ;
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 17);
  display.println(myTime);
  display.display();
  delay(500);
  myTime = "";
  display.clearDisplay();
  display.setCursor(0, 1);
  display.println(dayStamp);
  display.display();
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
  Serial.print("Buzzer! ");
  tone(buzzer, 900);
  delay(1000);
  noTone(buzzer);
}
// Untuk menyalakan pompa.
void pump() {
  digitalWrite(relay3, LOW);
  delay(9000);
  digitalWrite(relay3, HIGH);
}

void alaram_1() {
  if ( timeClient.getHours() == Time_Off && timeClient.getMinutes() == Minute_Off && timeClient.getSeconds() == 0) {
    Tone();
  }
}
void alaram_2() {
  if ( timeClient.getHours() == Time_On && timeClient.getMinutes() == Minute_On && timeClient.getSeconds() == 0) {
    Tone();
  }
}

void off_notif() {
  if ( timeClient.getHours() == Time_Off && timeClient.getMinutes() == Minute_Off && timeClient.getSeconds() == 0) {
    oled_on_screen();
  }
}
void on_notif() {
  if ( timeClient.getHours() == Time_On && timeClient.getMinutes() == Minute_On && timeClient.getSeconds() == 0) {
    oled_off_screen();
  }
}
