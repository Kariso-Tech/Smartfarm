/* ProgrammingElectronics.com */
//Mod By Christian Kariso

void setup() {

  Serial.begin(9600);
  pinMode(4, OUTPUT); /* LED circuit here */
  pinMode(5, OUTPUT); /* and here... */
  // print labels
  Serial.println("Smartfarm 0.1v");
  delay(1000);
  Serial.println("System Install");
}

void loop() {

  //Check if data is avilable
  if (Serial.available() > 1) {

    // read the sensor:
    int inByte = Serial.read();

    switch (inByte) {

      /* Turn on LED */
      case '1':
        Serial.println("Pump 1 Off"); // Print Unutk Serial Number
        digitalWrite(4, HIGH); //Pump 1 Off
        break;

      case '2':
        Serial.println("Pump 1 On"); // Print Unutk Serial Number
        digitalWrite(4, LOW); //Pump 1 On
        break;
      case '3':
        Serial.println("Pump 2 Off"); // Print Unutk Serial Number
        digitalWrite(5, HIGH);//Pump 2 On
        break;
      case '4':
        Serial.println("Pump 2 On"); // Print Unutk Serial Number
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
