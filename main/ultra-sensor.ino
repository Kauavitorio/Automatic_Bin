/*******************************************************************************
*
*    Copyright (c) 2021 Kauã Vitório
*    Responsible developer: https://github.com/Kauavitorio
*    Kauã Vitório Projects            
*
*******************************************************************************/

#define echoPin A2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin A1 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
extern long duration; // variable for the duration of sound wave travel
extern int distance; // variable for the distance measurement
extern bool estadoled;

void StartSensorUltra(){
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
}

void registerDistance(){
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor

  if(estadoled == false){
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");  
  }
   
}
