
#include "RTClib.h" // for the RTC
//LCD Libary
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//I2C LCD Addres
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
const int OffHour1 = 22;
const int OffMinute1 = 0;
//  On 13:00
const int OnHour1 = 6;
const int OnMinute1 = 0;
// Off 21:00
const int OffHour2 = 13;
const int OffMinute2 = 0;
// On 22:00
const int OnHour2 = 20;
const int OnMinute2 = 0;
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
  Serial.begin(9600);
  lcd.begin();
  // Coding Agar Waktu tidak terreset
  DateTime now = rtc.now();
  DateTime compiled = DateTime(__DATE__, __TIME__);
  if (now.unixtime() < compiled.unixtime()) {
    Serial.println("RTC is older than compile time! Updating");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
  //
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(relay1, OUTPUT);
  pinMode(relay12, OUTPUT);
  digitalWrite(relay1, LOW);// Relay For Growing Light Note: LOW = On (Pin 4)
  digitalWrite(relay12, LOW);// Relay For Growing Light Note: LOW = On (Pin 4)
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
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
  lcd.setCursor(0, 0);
  lcd.print(String() + hari + " " + tanggal + "/" + bulan + "/" + tahun);
  lcd.setCursor(0, 1);
  lcd.print(String() + jam + ":" + menit + ":" + detik + "" );
  delay(1000);

  // OffHour1-relay1
  if ((CurrentHour == OffHour1) && (CurrentMinute == OffMinute1)) {
    digitalWrite(relay1, HIGH);
    lcd.setCursor(9, 1);
    lcd.print(" GL OFF");
    lcd.print("     ");
  }
  // OnnHour1-relay1
  if  ((CurrentHour == OnHour1) && (CurrentMinute == OnMinute1)) {
    digitalWrite(relay1, LOW);
    lcd.setCursor(9, 1);
    lcd.print("GL ON");
    lcd.print("     ");

  }
  // OffHour1-relay12
  if ((CurrentHour == OffHour2) && (CurrentMinute == OffMinute2)) {
    digitalWrite(relay12, HIGH);
    lcd.setCursor(9, 1);
    lcd.print(" GL OFF");
    lcd.print("     ");
  }
  // OnHour2
  if  ((CurrentHour == OnHour2) && (CurrentMinute == OnMinute2 )) {
    digitalWrite(relay12, LOW);
    lcd.setCursor(9, 1);
    lcd.print(" GL ON");
    lcd.print("       ");


  }
}
