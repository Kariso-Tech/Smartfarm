
#include "RTClib.h" // for the RTC
//By Christian Kariso
RTC_DS1307 rtc;

// Define check in time
//24 Hour Format
//  Off 12:30
const int OffHour1 = 17;
const int OffMinute1 = 28;
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
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay12, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay12, LOW);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
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
    delay (1000);
    tone(buzzer, 1000, 5000);
    delay (1000);
    noTone(buzzer);
  }
  // OnnHour1-relay1
  if  ((CurrentHour == OnHour1) && (CurrentMinute == OnMinute1)) {
    digitalWrite(relay1, LOW);
  }
  // OffHour1-relay12
  if ((CurrentHour == OffHour2) && (CurrentMinute == OffMinute2)) {
    digitalWrite(relay12, HIGH);
    tone(buzzer, 1000); // Send 1KHz sound signal...
  }
  // OnHour2
  if  ((CurrentHour == OnHour2) && (CurrentMinute == OnMinute2 )) {
    digitalWrite(relay12, LOW);
    tone(buzzer, 1000); // Send 1KHz sound signal...

  }
}
