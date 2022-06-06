#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const unsigned int BUTTON_PIN = 7;

uint8_t clock[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
RTC_DS1307 RTC;

char daysOfTheWeek[7][12] = {"Ming", "Sen", "Sel", "Rab", "Kam", "Jum", "Sab"};
char bulan[12][12] = {"Jan", "Feb", "Mar", "Apr", "Mei", "Jun", "Jul", "Agu", "Sep", "Okt", "Nov", "Des"};

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  RTC.begin();
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  lcd.begin();
  //lcd.print("Belajar I2C LCD");

  if (! RTC.begin()) {
    Serial.println("RTC tidak ditemukan");
    while (1);
  }

  if (! RTC.isrunning()) {
    Serial.println("RTC tidak jalan!");
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // Mengatur tanggal dan waktu sesuai dengan waktu code di compile
  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));


}

void loop() {

  DateTime now = RTC.now();
  lcd.setCursor(0, 0);
  lcd.print("Pukul : ");

  if (now.hour() < 10) {
    lcd.print("0");
  }

  lcd.print(now.hour(), DEC);
  lcd.print(':');

  if (now.minute() < 10) {
    lcd.print("0");
  }

  lcd.print(now.minute(), DEC);
  lcd.print(':');

  if (now.second() < 10) {
    lcd.print("0");
  }

  lcd.print(now.second(), DEC);

  lcd.setCursor(0, 1);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.print(",");
  lcd.print(now.day(), DEC);
  lcd.print('/');

  //lcd.print(now.month(), DEC);
  lcd.print(bulan[now.month()]);
  lcd.print('/');
  lcd.print(now.year(), DEC);


  delay(1000);

}
