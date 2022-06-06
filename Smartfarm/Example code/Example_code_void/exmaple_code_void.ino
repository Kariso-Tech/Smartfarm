//The DIY Life
//By Michael Klements
//01/03/2017

void setup()
{
  pinMode(13, OUTPUT);  //Assign the on board LED to pin 13
}

void loop() 
{
  blinkLED();
  blinkLED();
  blinkLED();
}

void blinkLED()
{
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
