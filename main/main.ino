/*******************************************************************************
*
*    Projeto 54: Configurando um Display de 7 segmentos
*                 http://squids.com.br/arduino                
*
*******************************************************************************/
#include <Servo.h>
#include <EEPROM.h>

int speakerPin  = A0;
#define SERVO A3 // Porta Digital 6 PWM

// defines variables
long duration; // variable for the duration of sound wave travel
long minDistance = 20;
int distance; // variable for the distance measurement

int pushbutton = A4;
int workingLed = A5;
int baseDELAY = 150; 
int workingDELAY = 160; 
int notWorkingDELAY = 20; 
bool estadoled = false; // variavel de controle

Servo s; // Variável Servo
int pos; // Posição Servo

extern void StartEnconderDisplay();
extern void StartEnconderSond();
extern void StartSensorUltra();
extern void registerDistance();
extern void DisplayStatus();
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
  pinMode(pushbutton, INPUT_PULLUP); // define o pino do botao como entrada
  pinMode(workingLed, OUTPUT);// define LED como saida
    estadoled = EEPROM.read("wrokingStatus");
  
  DisplayStatus(0);
  Serial.println("-- System On -- "); // print some text in Serial Monitor
}

void loop() {
  if(estadoled == false){
    baseDELAY = workingDELAY;
    digitalWrite(workingLed, LOW); 
  
    registerDistance();

    if(distance <= minDistance){
       Serial.println("----- Minimal Distance -----");
       DisplayStatus(2);
       for(pos; pos <= 90; pos++)
        {
          s.write(pos);
          delay(5);
        }
       s.write(90);
    }else{
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
  
  if (digitalRead(pushbutton) == LOW) // Se o botão for pressionado
  {
      Serial.println("------------  Pause button pressed --------------");
      if(estadoled == false) {
        estadoled = true;
      } else if(estadoled == true) estadoled = false;
      digitalWrite(workingLed, estadoled); 
      beep(speakerPin, 1047, 100);
      delay(50);
      beep(speakerPin, 880, 100); 
      delay(50);
      beep(speakerPin, 1047, 100);
      delay(200);
      Serial.print("------------  Working Status: ");
      Serial.println(!estadoled);
     
      EEPROM.write("wrokingStatus", estadoled);
      pos = 0;
      s.write(pos);
  }
  
  delay(baseDELAY);
}
