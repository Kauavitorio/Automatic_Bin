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

void StartEnconderLevel(){
  pinMode(speakerPin , OUTPUT);
}

void checkNewLevel(){
    if(minDistance > 25){
      Serial.print("---  Min Distance: ");
      Serial.println(minDistance);
    }
  
     sensorLevel = analogRead(potenciometro);
     digitalWrite(MAXLED, LOW); 
     digitalWrite(MINLED, LOW);
    if(sensorLevel >= 0 && sensorLevel <= 150){ 
        digitalWrite(MINLED, HIGH); 
        minDistance = 25;
    }else if(sensorLevel >= 800 && sensorLevel <= 2000){
        digitalWrite(MAXLED, HIGH); 
        minDistance = 160;
    }else{
        if(sensorLevel >= 160 && sensorLevel <= 600){
           minDistance = sensorLevel / 6;
        }else if(sensorLevel >= 601 && sensorLevel <= 799){
          digitalWrite(MINLED, HIGH); 
          digitalWrite(MAXLED, HIGH); 
           minDistance = sensorLevel / 5;
        }
    }
}
