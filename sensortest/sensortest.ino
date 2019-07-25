/*QTI connected WITHOUT resistor:
B connected to GND
W connected to 5V
R connected to DIGITAL pin 6
*/
int QTIDataPin = 6;
//CHANGE THE FOLLOWING ONSITE to calibrate for lighting and height
//If sensed value goes higher than this, it is black
long calibratedBlack = 90;
//If sensed value goes lower than this, it is low
long calibratedWhite = 10;

void setup() {
  Serial.begin(9600);   //<- Uncomment if you need to debug
}

void loop() {
  //USE THIS VARIABLE WHEN YOU NEED TO CHECK THE COLOUR
  int colour = readColour(QTIDataPin);
  //Serial.println(colour);     //<- Uncomment if you need to debug
  //Serial.println(RCTime(QTIDataPin));   //<- Uncomment if you need to debug
}

//This function interprets the analog value read from sensor, giving 0 for white, 1 for black, 2 for "idk"
int readColour(int sensorIn) {
  long colour = RCTime(QTIDataPin);
  //THIS SENSES FOR BLACK (if rises above this value, it is black)
  //BLACK REPRESENTED BY A 1
  if (colour > calibratedBlack) colour = 1;
  //THIS SENSES FOR WHITE (if rises below this value, it is white)
  //WHITE REPRESENTED BY A 0
  else if (colour < calibratedWhite) colour = 0;
  //DEFAULT FOR ERROR HANDLING SET TO 2 (i.e. use this as a if this happens, keep doing what you're doing maybe)
  else colour = 2;

  return colour;
}

//This function returns an analog value
long RCTime(int sensorIn){
   long duration = 0;
   pinMode(sensorIn, OUTPUT);     
   digitalWrite(sensorIn, HIGH);  
   delay(1);                      
   pinMode(sensorIn, INPUT);      
   digitalWrite(sensorIn, LOW);   
   while(digitalRead(sensorIn)){  
      duration++;
   }
   return duration;
}
