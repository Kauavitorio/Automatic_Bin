/*******************************************************************************
*
*    Copyright (c) 2021 Kauã Vitório
*    Responsible developer: https://github.com/Kauavitorio
*    Kauã Vitório Projects            
*
*******************************************************************************/
#include <Servo.h>
#include <EEPROM.h>

int speakerPin  = A0;
#define SERVO 10 // Porta Digital 10 PWM
int MINLED = 12;
int MAXLED = 11;

// defines variables
long duration; // variable for the duration of sound wave travel
long minDistance = 20;
int distance; // variable for the distance measurement

int pushbutton = A4;
int workingLed = A5;
int baseDELAY = 150; 
int workingDELAY = 165; 
int notWorkingDELAY = 20; 
bool estadoled = false; // variavel de controle
bool idleControl = true; // variavel de controle idle

long idleTimer = 0;
long idleLimit = 300000;
int lastDistance = 0;

Servo s; // Variável Servo
int pos; // Posição Servo

const int potenciometro = A3; // pino de entrada do potenciômetro
int sensorLevel = 0;

extern void StartEnconderDisplay();
extern void StartEnconderSond();
extern void StartSensorUltra();
extern void StartEnconderLevel();
extern void registerDistance();
extern void DisplayStatus();
extern void checkNewLevel();
extern void onSong();
extern void beep();

void setup(){
  s.attach(SERVO);
  s.write(0); // Inicia motor posição zero
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04"); // print some text in Serial Monitor
  Serial.println("Starting up system -- "); // print some text in Serial Monitor
  StartEnconderSond();
  StartSensorUltra();
  StartEnconderDisplay();
  StartEnconderLevel();
  
  pinMode(pushbutton, INPUT_PULLUP); // define o pino do botao como entrada
  pinMode(workingLed, OUTPUT);
    estadoled = EEPROM.read("wrokingStatus");
    idleControl = EEPROM.read("idleControl");
  
  DisplayStatus(0);
  //onSong();
  Serial.println("-- System On -- "); // print some text in Serial Monitor
}

void loop() {
    registerDistance();
  if(estadoled == false){
    baseDELAY = workingDELAY;
    digitalWrite(workingLed, LOW); 

    if(distance <= minDistance){
        lastDistance = 0;
        idleControl = false;
        EEPROM.write("idleControl", idleControl);
       Serial.println("----- Minimal Distance -----");
       DisplayStatus(2);
       for(pos; pos <= 90; pos++)
        {
          s.write(pos);
          delay(5);
        }
       s.write(90);
    }else{
        idleControl = true;
        EEPROM.write("idleControl", idleControl);
       if(distance >= minDistance + 1 && distance <= minDistance + 20){
         DisplayStatus(1);
         for(pos; pos >= 0; pos--)
          {
            s.write(pos);
            delay(15);
          }
          s.write(pos);
       }else{
           DisplayStatus(0);
           for(pos; pos >= 0; pos--)
            {
              s.write(pos);
              delay(5);
            }
            s.write(pos);
       }
    }
  }else{
       baseDELAY = notWorkingDELAY;
       digitalWrite(workingLed, HIGH); 
       DisplayStatus(9);
  }

    countIdle();
    checkNewLevel();
  
  if (digitalRead(pushbutton) == LOW) // If the pause button is pressed
  {
      Serial.println("------------  Pause button pressed --------------");
      if(estadoled == false) {
        estadoled = true;
        idleTimer = 0;
      } else if(estadoled == true) estadoled = false;
      idleControl = !estadoled;
      digitalWrite(workingLed, estadoled); 
      beep(speakerPin, 1047, 100);
      delay(50);
      beep(speakerPin, 880, 100); 
      delay(200);
      Serial.print("------------  Working Status: ");
      Serial.println(!estadoled);
     
      EEPROM.write("wrokingStatus", estadoled);
      EEPROM.write("idleControl", idleControl);
      pos = 0;
      s.write(pos);
  }
  
  delay(baseDELAY);
}

void countIdle(){
  // idleLimit
  if(idleControl == true){
    int currentDistance = distance - 15;
    if(idleTimer <= idleLimit){
        if((lastDistance + 2) >= currentDistance || lastDistance == 0){
          idleTimer =  idleTimer + (workingDELAY + 15);
          lastDistance = currentDistance;
              
        }else {
          estadoled = false;
          idleTimer = 0;
          lastDistance = 0;
        }
        
          Serial.print("------------  Idle: ");
          Serial.println(idleTimer);
          
          if(idleTimer >= idleLimit) 
              Serial.println("------------  Idle ON ------------");
    }else{
      if(distance <= minDistance){
          estadoled = false;
          idleTimer = 0;
          lastDistance = 0;
      }
      else estadoled = true;
    }
  }
}
