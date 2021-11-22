/*******************************************************************************
*
*    Copyright (c) 2021 Kauã Vitório
*    Responsible developer: https://github.com/Kauavitorio
*    Kauã Vitório Projects            
*
*******************************************************************************/


extern void DisplayStatus();

// defines variables
extern int sensorLevel;
extern long minDistance;
extern const int potenciometro;
extern int MAXLED;
extern int MINLED;
extern int baseDELAY;
extern int workingLed;
extern bool estadoled;

void StartEnconderLevel(){
  pinMode(speakerPin , OUTPUT);
}

void checkNewLevel(){
    if(minDistance > 25){
      Serial.print("---  Min Distance: ");
      Serial.println(minDistance);
    }
  
     sensorLevel = analogRead(potenciometro);
    lightSystem(0);
    if(sensorLevel >= 0 && sensorLevel <= 150){ 
           lightSystem(1);
           minDistance = 25;
    }else if(sensorLevel >= 800 && sensorLevel <= 2000){
           lightSystem(2);
           minDistance = 160;
    }else{
        if(sensorLevel >= 160 && sensorLevel <= 600){
           minDistance = sensorLevel / 6;
        }else if(sensorLevel >= 601 && sensorLevel <= 799){
           lightSystem(3);
           minDistance = sensorLevel / 5;
        }
    }
}

void lightSystem(int where){
          digitalWrite(MINLED, LOW); 
          digitalWrite(MAXLED, LOW); 
  if(estadoled == false){
    if(where == 1)
          digitalWrite(MINLED, HIGH); 
      else if(where == 2)
          digitalWrite(MAXLED, HIGH); 
      else if(where == 3){
            digitalWrite(MINLED, HIGH); 
            digitalWrite(MAXLED, HIGH); 
      }
  }
}
