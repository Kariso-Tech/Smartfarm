
#include "RTClib.h" // for the RTC
//LCD Libary
#include <Wire.h>
//I2C LCD Addres
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//By Christian Kariso
RTC_DS1307 rtc;
// LCD Coding
//
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;
// Define check in time
//24 Hour Format
//  Off 22:00
const int OffHour1 = 22;
const int OffMinute1 = 0;
//  On 06:00
const int OnHour1 = 6;
const int OnMinute1 = 0;
// Off 13:00
const int OffHour2 = 13;
const int OffMinute2 = 0;
// On 20:00
const int OnHour2 = 20;
const int OnMinute2 = 0;
//Pompa
const int OnHour3 = 6;
const int OnMinute3 = 0;
// Relayy
// Waktu
int CurrentHour;
int CurrentMinute;
//Growing Light
// Relay1=Relay12
const int relay1 = 4;
const int relay12 = 4;
// Pompa Air



void setup() {
  Serial.begin(9600);
  display.begin();
  // Coding Agar Waktu tidak terreset
  DateTime now = rtc.now();
  DateTime compiled = DateTime(__DATE__, __TIME__);
  if (now.unixtime() < compiled.unixtime()) {
    Serial.println("Updating RTC");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
  //
  pinMode(relay1, OUTPUT);
  pinMode(relay12, OUTPUT);
  digitalWrite(relay1, LOW);// Relay For Growing Light Note: LOW = On (Pin 4)
  digitalWrite(relay12, LOW);// Relay For Growing Light Note: LOW = On (Pin 4)


}
void loop() {
  DateTime now = rtc.now();
  hari    = dataHari[now.dayOfTheWeek()];
  tanggal = now.day();
  bulan   = now.month();
  tahun   = now.year();
  jam     = now.hour();
  menit   = now.minute();
  detik   = now.second();

  // LCD AND TIME

  ///
  // Save check in time;
  CurrentHour = now.hour();
  CurrentMinute = now.minute();
  //
  //
  //
  display.setTextSize(1);          // text size
  display.setTextColor(WHITE); // Set text to plot foreground and background colours
  display.setCursor(0, 20);        // position to display
  display.println("Testing");
  display.display();               // show on OLED
  //Text Berada diatas coding ini ,Tidak akan blink
  //Tanggal
  display.setTextSize(1);          // text size
  display.setTextColor(WHITE);     // text color
  display.setCursor(0, 10);        // position to display
  display.println(String() + hari + " " + tanggal + "/" + bulan + "/" + tahun);
  display.display();               // show on OLED

  //Waktu
  display.setTextSize(1);          // text size
  display.setTextColor(WHITE);     // text color
  display.setCursor(0, 0);        // position to display
  display.println(String() + jam + ":" + menit + ":" + detik + "" );
  display.display();               // show on OLED
  delay(1000);
  display.clearDisplay();

  //Text



  // OffHour1-relay1
  if ((CurrentHour == OffHour1) && (CurrentMinute == OffMinute1)) {
    digitalWrite(relay1, HIGH);
    display.setCursor(9, 1);
    display.print(" GL OFF");

  }
  // OnnHour1-relay1
  if  ((CurrentHour == OnHour1) && (CurrentMinute == OnMinute1)) {
    digitalWrite(relay1, LOW);
    display.setCursor(9, 1);
    display.print("GL ON");


  }
  // OffHour1-relay12
  if ((CurrentHour == OffHour2) && (CurrentMinute == OffMinute2)) {
    digitalWrite(relay12, HIGH);
    display.setCursor(9, 1);
    display.print(" GL OFF");

  }
  // OnHour2
  if  ((CurrentHour == OnHour2) && (CurrentMinute == OnMinute2 )) {
    digitalWrite(relay12, LOW);
    display.setCursor(9, 1);
    display.print(" GL ON");

  }
  if  ((CurrentHour == OnHour3) && (CurrentMinute == OnMinute3 )) {
    digitalWrite(relay12, LOW);
    display.setCursor(9, 1);
    display.print(" GL ON");


  }
}
