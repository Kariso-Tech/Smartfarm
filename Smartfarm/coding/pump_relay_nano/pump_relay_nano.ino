// Mod By Christian Kariso
// Control pump with buzzer
// Nodemcu harus #define dulu baru buat pinMode

// Declare 
int relay1 = D4;
int relay2 = 8;
const int buzzer = 11;
void setup() {

  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(relay1, OUTPUT); /* LED circuit here */
  pinMode(relay2, OUTPUT); /* and here... */
  // print labels
  Serial.println("On Off Switch");
}

void loop() {

  //Check if data is avilable
  if (Serial.available() > 1) {

    // read the sensor:
    int inByte = Serial.read();

    switch (inByte) {

      /* Turn on LED */
      case '1':
        Serial.println("Pump On"); // Print Unutk Serial Number
        Tone();
        pump();
        break;

      case '2':
        Serial.println("Testing Buzzer"); // Print Unutk Serial Number
        Tone();
        break;
      case '3':
        Serial.println("On"); // Print Unutk Serial Number
        digitalWrite(relay2, HIGH);//Pump 2 On
        break;
      case '4':
        Serial.println("On"); // Print Unutk Serial Number
        digitalWrite(relay2, LOW);//Pump 2 Off
        break;
      case '5':
        Serial.println("Offline Mode"); // Print Unutk Serial Number
        digitalWrite(relay1, HIGH);
        digitalWrite(relay2, HIGH);
        break;
      case '6':
        Serial.println("Testing Mode Mode"); // Print Unutk Serial Number
        digitalWrite(relay1, LOW);
        digitalWrite(relay2, LOW);
        break;
        /* Turn off all LEDs and Stand down Missle Defense System */

    }
  }
}

void pump() {
  digitalWrite(relay1, LOW);
  delay(3000);
  digitalWrite(relay1, HIGH);
}

void Tone() {
  tone(buzzer, 700);
  delay(1000);
  noTone(buzzer);
}
