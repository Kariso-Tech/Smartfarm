// Variable Declare 
int pump1 = 4;
int pump2 = 5;
void setup() {

  Serial.begin(9600);
//  
  pinMode(pump1, OUTPUT); 
  pinMode(pump2, OUTPUT); 
  // print labels
  Serial.println("On Off Switch");
  Serial.println("1.Module 1 On");
  Serial.println("2.Module 1 Off");
  Serial.println("3.Module 2 On");
  Serial.println("4.Module 2 Off");
  Serial.println("5.Offline Mode/ Emergency ");
  Serial.println("6.Testing Mode Mode/Debug ");
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
        digitalWrite(4, HIGH); //Pump 1 On
        break;

      case '1':
        Serial.println("Off"); // Print Unutk Serial Number
        digitalWrite(4, LOW); //Pump 1 Off
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
        Serial.println("Offline Mode"); // Mematikan semua module / Sangat disarankan untuk menggunakan ini ketika emergency
        digitalWrite(5, HIGH);
        digitalWrite(4, HIGH);
        break;
      case '6':
        Serial.println("Testing Mode Mode/Debug "); // Print Unutk Serial Number
        digitalWrite(5, LOW);
        digitalWrite(4, LOW);
        delay(1000);
        digitalWrite(5, HIGH);
        digitalWrite(4, HIGH);
        break;

    }
  }
}
