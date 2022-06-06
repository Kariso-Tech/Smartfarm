
#include "RTClib.h" // for the RTC
//LCD Libary
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//By Christian Kariso
RTC_DS1307 rtc;
// LCD Coding
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;
// Define check in time
//24 Hour Format
//  Off 12:30
const int OffHour1 = 20;
const int OffMinute1 = 8;
//  On 13:00
const int OnHour1 = 16;
const int OnMinute1 = 35;
// Off 21:00
const int OffHour2 = 16;
const int OffMinute2 = 40;
// On 22:00
const int OnHour2 = 16;
const int OnMinute2 = 50;
//Buzzer

////////////////////////////////// Relayy
// Waktu
int CurrentHour;
int CurrentMinute;
//Growing Light
// Relay1=Relay12
const int relay1 = 4;
const int relay12 = 4;
const int buzzer = 6; //buzzer to arduino pin 9

void setup() {

  rtc.begin();
  // Waktu tersingkronasi dengan Komputer
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay12, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay12, LOW);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  lcd.begin();
}
void loop() {
  hari    = dataHari[now.dayOfTheWeek()];
  tanggal = now.day();
  bulan   = now.month();
  tahun   = now.year();
  jam     = now.hour();
  menit   = now.minute();
  detik   = now.second();
  lcd.setCursor(0, 0);
  lcd.print(String() + hari + "," + tanggal + "-" + bulan + "-" + tahun);
  lcd.setCursor(0, 1);
  lcd.print(String() + jam + ":" + menit + ":" + detik + " "  + ".C ");
  delay(1000);
  DateTime now = rtc.now();
  // LCD AND TIME

  ///
  // Save check in time;
  CurrentHour = now.hour();
  CurrentMinute = now.minute();
  Serial.println(now.hour());
  Serial.println(now.minute());
  delay(2000);
  // OffHour1-relay1
  if ((CurrentHour == OffHour1) && (CurrentMinute == OffMinute1)) {
    digitalWrite(relay1, HIGH);
    //LCD Screen
    lcd.backlight();
    lcd.print("Light Off");
  }
  // OnnHour1-relay1
  if  ((CurrentHour == OnHour1) && (CurrentMinute == OnMinute1)) {
    digitalWrite(relay1, LOW);
    lcd.backlight();
    lcd.print("Light On");

  }
  // OffHour1-relay12
  if ((CurrentHour == OffHour2) && (CurrentMinute == OffMinute2)) {
    lcd.backlight();
    lcd.print("Light Off");

  }
  // OnHour2
  if  ((CurrentHour == OnHour2) && (CurrentMinute == OnMinute2 )) {
    digitalWrite(relay12, LOW);

    lcd.backlight();
    lcd.print("Light On");

  }
}
