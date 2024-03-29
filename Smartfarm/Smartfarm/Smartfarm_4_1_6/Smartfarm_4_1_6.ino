// Arduino libary
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <RTClib.h>
// Oled libary
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Oled Config
// Tinggi dan lebar dari oled
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// Untuk declare SSD1306 I2C
// Nodemcu
// SDA = D4 ,SCL = D5
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Define.
// Declare untuk hardware.
// Untuk ESP.
// #define var Dx.
// Dx = Pin.
// var = variable.
#define relay1 D3
#define relay2 D4
#define buzzer D5



// Wifi-Config
// SSID Wi-fi dan password wifi.
// Harap disesuaiakn sebelum upload! .
const char *ssid     = "Kakas_Valley_Tech";
const char *password = "kariso-tech";
// Time Config
// UTC Time
// Bangkok = UTC+8
// utcOffsetInSeconds= UTC*(60m)*(60s)+(utc)(60)
// unutk utc berlaku jika zona waktu seperti
// UTC+03:30
// utcOffsetInSeconds= ((3)*60*60)+((30)*(60))
// Refrensi https://microcontrollerslab.com/iot-analog-digital-clock-oled-esp32-esp8266/
// -------------------------------------------------------------------------------------------
const long utcOffsetInSeconds = 28800;

// myTime; String
// Interger dan string untuk waktu.
int Secs;
int Minutes;
int Hours;
String myTime;
// Interger dan string untuk tanggal
String Date;
String formattedDate;
String dayStamp;
// Timer Config.
// Interger dan string untuk waktu
// Time_Off & Minute_Off adalah variable untuk mematikan relay.
// Time_On & Minute_On adalah variable untuk menyalakan  relay.
// Sebagai contoh
// Jika ingin mematikan relay pada jam 16:04 (04:04PM)
// Maka Time_Off = 16; & Minute_Off = 4;
// -------------------------------------------------------------------------------------------
// Time_On & Minute_On adalah variable untuk menyalakan relay/
// Sebagai contoh
// Jika ingin menyalakan relay pada jam 16:08 (04:08PM)
// Maka Time_On = 16; & Minute_On = 8;
// -------------------------------------------------------------------------------------------
int Time_Off = 17;
int Minute_Off = 32;
//--------------------------------------------------------------------------------------------
int Time_On = 17;
int Minute_On = 33;

// Define NTP Client unutk mendapatkan waktu dri internet
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);
//--------------------------------------------------------------------------------------------
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  pinMode(relay1, OUTPUT); /*Untuk growing light */
  pinMode(relay2, OUTPUT); /* Untuk pompa mini */
  pinMode(buzzer, OUTPUT); /*Untuk buzzer */
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  // Loding screen dan status internet
  while ( WiFi.status() != WL_CONNECTED ) {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, -0);
    display.println("System Booting......");
    display.display();
    display.clearDisplay();
    delay(3000);
    display.setCursor(0, -0);
    display.println("Connect To");
    display.println(ssid);
    display.setCursor(0, 2);
    display.display();
    display.clearDisplay();
    delay(2000);
    display.clearDisplay();
    display.setCursor(0, -0);
    display.println("Internet Ok");
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setCursor(0, -0);
    display.println("Welcome To SF-4.1.6");
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setCursor(0, -0);
    display.println("Desgin By @kakastechid");
    display.display();
    delay(3000);
    display.clearDisplay();
  }
  timeClient.begin();
}
void loop() {
  timeClient.update();
  opration();
  lcdtime();
}
// Untuk melakukan eksekusi untuk growing light.
void opration() {
  if ( timeClient.getHours() == Time_Off && timeClient.getMinutes() == Minute_Off) {
    lighton();
    oled_on_screen();
  }
  if ( timeClient.getHours() == Time_On && timeClient.getMinutes() == Minute_On) {
    lightoff();
    oled_off_screen();
  }
}
void oled_on_screen() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 25);
  display.println("LED ON");
  display.display();

}
void oled_off_screen() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 25);
  display.println("LED OFF");
  display.display();
}
void lcdtime() {
  // Untuk menampilkan tanggal pada Oled
  formattedDate = timeClient.getFormattedDate();
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  //
  Secs = timeClient.getSeconds();
  Hours = timeClient.getHours();
  Minutes = timeClient.getMinutes();
  // Untuk menampilkan waktu pada Oled
  myTime =  myTime + Hours + ":" + Minutes + ":" + Secs ;
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 15);
  display.println("Waktu: " + myTime);
  display.display();
  delay(1000);
  myTime = "";
  display.clearDisplay();
  display.setCursor(0, 1);
  display.println("Tanggal : " + dayStamp);
  display.display();
}
// Untuk menyalakan lampu.
void lighton() {
  digitalWrite(relay1, LOW);
}
// Untuk mematikan lampu.
void lightoff() {
  digitalWrite(relay1, HIGH);
}
// Untuk menyalakan pompa.
void pump() {
  digitalWrite(relay2, LOW);
  delay(9000);
  digitalWrite(relay2, HIGH);
}
