
#include <RTClib.h> // for the RTC

// Instance of the class for RTC
//By Christian Kariso
RTC_DS1307 rtc;

// Define check in time
//24 Hour Format
//Pagi Jam On 06:00
const int ONHour1 = 15;
const int ONMinute1 = 10;
//Siang Jam Off 11:00
const int OFFHour1 = 15;
const int OFFMinute1 = 15;
//Siang On 11:30
const int OnHour2 = 15;
const int OnMinute2 = 20;
//Malam Off 19:00
const int OffHour2 = 15;
const int OffMinute2 = 25;
//Malam On 23:00
const int OnHour3 = 23;
const int OnMinute3 = 00;

////////////////////////////////// Relayy



int CurrentHour;
int CurrentMinute;
// Pins for LEDs and buzzer


//Growing Light
const int relay1 = 8;
const int relay2 = 3;
const int relay12 = 8;


void setup() {
  Serial.begin(9600);
  rtc.begin();
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay12, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay12, HIGH);
}
void loop() {
  DateTime now = rtc.now();
  // Save check in time;
  CurrentHour = now.hour();
  CurrentMinute = now.minute();
  Serial.println(CurrentHour);
  Serial.println(CurrentMinute);
  if ((CurrentHour == ONHour1) && (CurrentMinute == ONMinute1)) {
    digitalWrite(relay1, LOW);
    Serial.println("LIGHT ON");
  }
  if  ((CurrentHour == OFFHour1) && (CurrentMinute == OFFHour1)) {
    digitalWrite(relay1, HIGH);
    Serial.println("LIGHT OFF");
  }
  if ((CurrentHour == OnHour2) && (CurrentMinute == OnMinute2)) {
    digitalWrite(relay12, LOW);
    Serial.println("LIGHT ON");
  }
  if  ((CurrentHour == OffHour2) && (CurrentMinute == OffMinute2)) {
    digitalWrite(relay12, HIGH);
    Serial.println("LIGHT OFF");
  }
}
