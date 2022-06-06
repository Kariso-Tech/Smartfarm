/* ProgrammingElectronics.com */
//Mod By Christian Kariso

int pump1 = 4;
int pump2 = 5;
void setup() {

  Serial.begin(9600);
  pinMode(pump1, OUTPUT); /* LED circuit here */
  pinMode(pump2, OUTPUT); /* and here... */
  // print labels
  Serial.println("On Off Switch");
}

void loop() {

  //Check if data is avilable
  if (Serial.available() > 0) {

    // read the sensor:
    int inByte = Serial.read();

    switch (inByte) {

      /* Turn on LED */
      case '2':
        Serial.println("On"); // Print Unutk Serial Number
        digitalWrite(4, HIGH); //Pump 1 Off
        break;

      case '1':
        Serial.println("Off"); // Print Unutk Serial Number
        digitalWrite(4, LOW); //Pump 1 On
        break;
      case '4':
        Serial.println("On"); // Print Unutk Serial Number
        digitalWrite(5, HIGH);//Pump 2 On
        break;
      case '3':
        Serial.println("On"); // Print Unutk Serial Number
        digitalWrite(5, LOW);//Pump 2 Off
        break;
      case '5':
        Serial.println("Offline Mode"); // Print Unutk Serial Number
        digitalWrite(5, HIGH);
        digitalWrite(4, HIGH);
        break;
      case '6':
        Serial.println("Testing Mode Mode"); // Print Unutk Serial Number
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        break;
        /* Turn off all LEDs and Stand down Missle Defense System */

    }
  }
}
