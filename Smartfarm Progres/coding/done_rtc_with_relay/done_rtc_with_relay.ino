
#include <RTClib.h> // for the RTC

// Instance of the class for RTC
//By Christian Kariso
RTC_DS1307 rtc;

// Define check in time
//24 Hour Format
//1. Pagi Jam On 06:00
const int OnHour1 = 1;
const int OnMinute1 = 10;
//2. Siang Jam Off 11:00
const int OffHour1 = 1;
const int OffMinute1 = 15;
//3. Siang On 11:30
const int OnHour2 = 1;
const int OnMinute2 = 20;
//4. Malam Off 19:00
const int OffHour2 = 1;
const int OffMinute2 = 25;
//5. Malam On 23:00
const int OnHour3 = 1;
const int OnMinute3 = 30;

////////////////////////////////// Relayy
const int ONHourx1 = 11;
const int ONMinutex1 = 13;
const int OFFHourx1 = 11;
const int OFFMinutex1 = 14;


int CurrentHour;
int CurrentMinute;
// Pins for LEDs and buzzer


//Growing Light
const int relay1 = 8;
const int relay2 = 3;



void setup() {
  Serial.begin(9600);
  rtc.begin();
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);

}
void loop() {
  DateTime now = rtc.now();
  // Save check in time;
  CurrentHour = now.hour();
  CurrentMinute = now.minute();
  Serial.println(CurrentHour);
  Serial.println(CurrentMinute);
  for ((CurrentHour == OnHour1; CurrentMinute == OnMinute1)) {
    digitalWrite(relay1, LOW);
  }
}
