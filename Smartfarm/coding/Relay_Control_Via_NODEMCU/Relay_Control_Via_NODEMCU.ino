/* ProgrammingElectronics.com */
// Mod By Christian Kariso
// Unutk coding menggunakan Nodemcu tidak sama dengan coding pada arduino
// Nodemcu harus #define dulu baru buat pinMode
#define relay1 D3
#define relay2 D5
void setup() {

  Serial.begin(9600);
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
        Serial.println("On"); // Print Unutk Serial Number
        digitalWrite(relay1, HIGH); //Pump 1 Off
        break;

      case '2':
        Serial.println("Off"); // Print Unutk Serial Number
        digitalWrite(relay1, LOW); //Pump 1 On
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
