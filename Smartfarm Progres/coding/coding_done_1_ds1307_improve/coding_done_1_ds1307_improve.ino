
#include "RTClib.h" // for the RTC
//By Christian Kariso
RTC_DS1307 rtc;

// Define check in time
//24 Hour Format
//  Off 12:30
const int OffHour1 = 16;
const int OffMinute1 = 21;
//  On 13:00
const int OnHour1 = 16;
const int OnMinute1 = 23;
// Off 21:00
const int OffHour2 = 16;
const int OffMinute2 = 26;
// On 22:00
const int OnHour2 = 16;
const int OnMinute2 = 28;
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
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  Serial.begin(19200);
  pinMode(relay1, OUTPUT);
  pinMode(relay12, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay12, LOW);
  digitalWrite(buzzer, HIGH); // Set buzzer - pin 9 as an output
}
void loop() {
  DateTime now = rtc.now();
  // Save check in time;
  CurrentHour = now.hour();
  CurrentMinute = now.minute();
  Serial.println(now.hour());
  Serial.println(now.minute());
  delay(2000);
  // OffHour1-relay1
  if ((CurrentHour == OffHour1) && (CurrentMinute == OffMinute1)) {
    digitalWrite(relay1, HIGH);
  }
  // Jika CurrentHour == OffHourX dan CurrentMinute == OffMinuteX maka buzzer akan berbunyi
  if ((CurrentHour == OffHour1) && (CurrentMinute == OffMinute1)); {
    tone(buzzer, 500);
    delay(2000);
    // Buzzer akan berhenti berbunyi
    noTone(buzzer);
    if ((CurrentHour == OffHour1) && (CurrentMinute == OffMinute1));
  }
  // OnnHour1-relay1
  if  ((CurrentHour == OnHour1) && (CurrentMinute == OnMinute1)) {
    digitalWrite(relay1, LOW);
  }
  // Jika CurrentHour == OffHourX dan CurrentMinute == OffMinuteX maka buzzer akan berbunyi
  if ((CurrentHour == OnHour1 ) && (CurrentMinute == OnMinute1 )); {
    // Buzzer akan 500kz
    tone(buzzer, 500);
    delay(2000);
    // Buzzer akan berhenti berbunyi
    noTone(buzzer);
    if ((CurrentHour == OnHour1) && (CurrentMinute == OnMinute1));
  }
  // OffHour1-relay12
  if ((CurrentHour == OffHour2) && (CurrentMinute == OffMinute2)) {
    digitalWrite(relay12, HIGH);
  }
  // Jika CurrentHour == OffHourX dan CurrentMinute == OffMinuteX maka buzzer akan berbunyi
  if ((CurrentHour == OffHour2) && (CurrentMinute == OffMinute2)); {
    // Buzzer akan 500kz
    tone(buzzer, 500);
    delay(2000);
    // Buzzer akan berhenti berbunyi
    noTone(buzzer);
    if ((CurrentHour == OffHour2) && (CurrentMinute == OffMinute2));
  }
  // OnHour2
  if  ((CurrentHour == OnHour2) && (CurrentMinute == OnMinute2 )) {
    digitalWrite(relay12, LOW);
  }
  // Jika CurrentHour == OffHourX dan CurrentMinute == OffMinuteX maka buzzer akan berbunyi
  if ((CurrentHour == OnHour2) && (CurrentMinute == OnMinute2)); {
    // Buzzer akan 500kz
    tone(buzzer, 500);
    delay(2000);
    // Buzzer akan berhenti berbunyi
    noTone(buzzer);
    if ((CurrentHour == OnHour2) && (CurrentMinute == OnMinute2));
  }
}
