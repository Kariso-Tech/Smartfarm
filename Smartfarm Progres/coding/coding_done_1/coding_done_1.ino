
#include "RTClib.h" // for the RTC

//By Christian Kariso
RTC_DS3231 rtc;


// Define check in time
//24 Hour Format
//  Off 12:30
const int OffHour1 = 12;
const int OffMinute1 = 00;
//  On 13:00
const int OnHour1 = 13;
const int OnMinute1 = 0;
// Off 21:00
const int OffHour2 = 21;
const int OffMinute2 = 0;
// On 22:00
const int OnHour2 = 22;
const int OnMinute2 = 00;
//Buzzer
const int buzzer = 9; //buzzer to arduino pin 9

////////////////////////////////// Relayy
// Waktu
int CurrentHour;
int CurrentMinute;
//Growing Light
// Relay1=Relay12
const int relay1 = 4;
const int relay12 = 4;


void setup() {
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  Serial.begin(9600);
  rtc.begin();
  pinMode(relay1, OUTPUT);
  pinMode(relay12, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay12, LOW);

}
void loop() {
  DateTime now = rtc.now();
  // Save check in time;
  CurrentHour = now.hour();
  CurrentMinute = now.minute();
  Serial.println(now.hour());
  Serial.println(now.minute());
  delay(2000);
  if ((CurrentHour == OffHour1) && (CurrentMinute == OffMinute1)) {
    digitalWrite(relay1, HIGH);
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
  }
  if  ((CurrentHour == OnHour1) && (CurrentMinute == OnHour1)) {
    digitalWrite(relay1, LOW);
    Serial.println("LIGHT OFF");
  }
  if ((CurrentHour == OffHour2) && (CurrentMinute == OffMinute2)) {
    digitalWrite(relay12, HIGH);
    Serial.println("LIGHT ON");
  }
  if  ((CurrentHour == OnHour2) && (CurrentMinute == OnHour2)) {
    digitalWrite(relay12, LOW);
    Serial.println("LIGHT OFF");
  }
  if  ((CurrentHour == OnHour2) && (CurrentMinute == OnHour2)) {
    digitalWrite(relay12, LOW);
    Serial.println("LIGHT OFF");
  }
}
