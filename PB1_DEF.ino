///*http://bildr.org/2011/02/74hc595/*/
int SER_Pin = 8;   //pin 14 on the 75HC595
int RCLK_Pin = 9;  //pin 12 on the 75HC595
int SRCLK_Pin = 10; //pin 11 on the 75HC595
//Initial Checking
int bulean = 0;

//How many of the shift registers - change this
#define number_of_74hc595s 4

//maximum range to change status of sky in the star, It is meaning from 0 till 12 LED´s are skies, from 13 till the end 32 LED´s belong to Estrella de Belen
//Si la estrella de belen esta formada por 19 LED esta constante tiene que valer 18
#define MAXPINSTARSKY 18

#define BLAST_ON 5

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8

//Numbers of effects
#define NUMEFECTOS 17
/*
   0.  SecuencialLED1by1(50,5000);
   1.  RandomBlinkSkyStarandEBONandOFF(250,5000);
   2.  AllLEDOFF(5000);
   3.  AllLEDON(5000);
   4.  BelenStarONrstOFF(50,5000);
   5.  BelenStarOFFrestON(50,5000);
   6.  AllRandom(50,5000);
   7.  BelenStarsecuencial1by1andskyOFF(50,5000);
   8.  BelenStarOFFrestONsecuencial1by1(50,5000);
   9.  AllLEDON1by1(50,5000);
   10. BelenStarON1by1(50,5000);
   11. AllONandOff1by1(50,5000);
   12. OFF1by1Secuencial(50,5000);
   13. BelenStarOFF1by1restOFF(250,5000);
   14. ALLONandbelenstaroff1by1(150,5000);
   15. ALLblinking(150,5000);
   16. Blastby2inBELENstar(150,5000);
    
    MAS FUCNIONES
    *  TODAS APAGADAS Y ENCENDER POCO A POCO LA ESTRELLA DE BELEN, ¿TERMINAR PARPADEANDO?   
*/

boolean registers[numOfRegisterPins];

void setup(){
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);


  //reset all register pins
  clearRegisters();
  writeRegisters();
  bulean = 0;
}               


//set all register pins to LOW
void clearRegisters(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
     registers[i] = LOW;
  }
} 


//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
//Only call once after the values are set how you need.
void writeRegisters(){

  digitalWrite(RCLK_Pin, LOW);

  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);

    int val = registers[i];

    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);

  }
  digitalWrite(RCLK_Pin, HIGH);

}

//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value){
  registers[index] = value;
}




void ApplyEfecto(int iEfecto){
   
   switch (iEfecto) {
    case 0:
      SecuencialLED1by1(random(50,300),random(5000,30000));
    break;
    case 1:
      RandomBlinkSkyStarandEBONandOFF(random(250,900),random(5000,30000));
    break;
    case 2:
      AllLEDOFF(random(5000,30000));
    break;
    case 3:
      AllLEDON(random(5000,30000));
    break;
    case 4:
      BelenStarONrstOFF(random(50,300),random(5000,30000));
    break;
    case 5:
      BelenStarOFFrestON(random(50,300),random(5000,30000));
    break;
    case 6:
      AllRandom(random(250,900),random(5000,30000));
    break;
    case 7:
      BelenStarsecuencial1by1andskyOFF(random(50,300),random(5000,30000));
    break;
    case 8:
      BelenStarOFFrestONsecuencial1by1(random(50,300),random(5000,30000));
    break;
    case 9:
      AllLEDON1by1(random(50,300),random(5000,30000));
    break;
    case 10:
      BelenStarON1by1(random(50,300),random(5000,30000));
    break;
    case 11:
      AllONandOff1by1(random(50,300),random(5000,30000));
    break;
   case 12:
      OFF1by1Secuencial(random(200,900),random(5000,30000));
   break;
   case 13:
      BelenStarOFF1by1restOFF(random(200,900),random(5000,30000));
   break;
   case 14:
      ALLONandbelenstaroff1by1(random(150,300),random(5000,30000));
   break;
   case 15:
      ALLblinking(random(5000,30000));
   break;
   case 16:
      BlastbyoffsetinBELENstar(random(80,600),random(5000,30000),random(1,3));
   break;
   }
}

void BlastbyoffsetinBELENstar(unsigned long delayedtime,unsigned long runningtime,byte ioffset){
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
  //AllLEDOFF(5);
  while (runningtime >= t_actualizado - tiempo) {
    int LedON = MAXPINSTARSKY;
    while (LedON <= numOfRegisterPins) {
      for(int i = numOfRegisterPins - 1; i >=  0; i--){
         if ((i == LedON) && (i > MAXPINSTARSKY)){
          setRegisterPin(i,HIGH);
          PersonalDelay(delayedtime);
          for(int j = 1; j <= ioffset; j++){
            setRegisterPin(i+j,HIGH);
          }
         }
      }
      writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
      for(int i = numOfRegisterPins - 1; i >=  0; i--){
         if ((i == LedON) && (i > MAXPINSTARSKY)){
          setRegisterPin(i,LOW);
          PersonalDelay(delayedtime);
          for(int j = 1; j <= ioffset; j++){
            setRegisterPin(i+j,HIGH);
          }
         }
      }      
      writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
      t_actualizado = millis();
      LedON++;
    }
    if (LedON > numOfRegisterPins){
      AllLEDOFF(5);
    }
  }  
}

void ALLblinking(unsigned long runningtime){
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
  
  //AllLEDOFF(5);
  while (runningtime >= t_actualizado - tiempo) {
     AllLEDON(1000);
     t_actualizado = millis();
     AllLEDOFF(1000);
  } 
  
}

void ALLONandbelenstaroff1by1(unsigned long delayedtime,unsigned long runningtime){
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
  //AllLEDON(5);
  while (runningtime >= t_actualizado - tiempo) {
    int LedON = MAXPINSTARSKY;
    while (LedON <= numOfRegisterPins) {
      for(int i = numOfRegisterPins - 1; i >  MAXPINSTARSKY; i--){
         if (i == LedON){
          setRegisterPin(i,LOW); 
         } else {
          setRegisterPin(i,HIGH); 
         }
      }
      writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
      PersonalDelay(delayedtime);
      t_actualizado = millis();
      LedON++;
    }
    if (LedON > numOfRegisterPins){
      AllLEDON(5);
    }
  }
}

void BelenStarOFF1by1restOFF(unsigned long delayedtime,unsigned long runningtime){
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
  //AllLEDOFF(5);
  while (runningtime >= t_actualizado - tiempo) {
    int LedON = MAXPINSTARSKY;
    while (LedON <= numOfRegisterPins) {
      for(int i = numOfRegisterPins - 1; i >  MAXPINSTARSKY; i--){
         if (i == LedON){
          setRegisterPin(i,LOW); 
         } else {
          setRegisterPin(i,HIGH); 
         }
      }
      writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
      PersonalDelay(delayedtime);
      t_actualizado = millis();
      LedON++;
    }
    if (LedON > numOfRegisterPins){
      AllLEDOFF(5);
    }
  }
}

void OFF1by1Secuencial(unsigned long delayedtime,unsigned long runningtime){
  
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
 // AllLEDON(5);
  while (runningtime >= t_actualizado - tiempo) {
    int LedON = 0;
    while (LedON <= numOfRegisterPins) {
      for(int i = numOfRegisterPins - 1; i >=  0; i--){
         if (i == LedON){
          setRegisterPin(i,LOW); 
         } else {
          setRegisterPin(i,HIGH); 
         }
      }
      writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
      PersonalDelay(delayedtime);
      t_actualizado = millis();
      LedON++;
    }
    if (LedON > numOfRegisterPins){
      AllLEDON(5);
    }
  }
    
}
void AllONandOff1by1(unsigned long delayedtime,unsigned long runningtime){

  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
 // AllLEDON(5);
  while (runningtime >= t_actualizado - tiempo) {
    int LedON = 0;
    while (LedON <= numOfRegisterPins) {
      for(int i = numOfRegisterPins - 1; i >=  0; i--){
         if (i == LedON){
          setRegisterPin(i,LOW); 
         }
      }
      writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
      PersonalDelay(delayedtime);
      t_actualizado = millis();
      LedON++;
    }
    if (LedON > numOfRegisterPins){
      AllLEDON(5);
    }
  }
}
void BelenStarON1by1(unsigned long delayedtime,unsigned long runningtime){
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
 // AllLEDOFF(5);
  while (runningtime >= t_actualizado - tiempo) {
    int LedON = 0;
    while (LedON <= numOfRegisterPins) {
      for(int i = numOfRegisterPins - 1; i >=  0; i--){
         if ((i == LedON) && (i > MAXPINSTARSKY)){
          setRegisterPin(i,HIGH); 
         } else {
          setRegisterPin(i,LOW); 
         }
      }
      writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
      PersonalDelay(delayedtime);
      t_actualizado = millis();
      LedON++;
    }
    if (LedON > numOfRegisterPins){
      AllLEDOFF(5);
    }
  }
}

void AllLEDON1by1(unsigned long delayedtime,unsigned long runningtime){
  
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
  AllLEDOFF(5);
  while (runningtime >= t_actualizado - tiempo) {
    int LedON = 0;
    while (LedON <= numOfRegisterPins) {
      for(int i = numOfRegisterPins - 1; i >=  0; i--){
         if (i <= LedON){
          setRegisterPin(i,HIGH); 
         } else {
          setRegisterPin(i,LOW); 
         }
      }
      writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
      PersonalDelay(delayedtime);
      t_actualizado = millis();
      LedON++;
    }
    if (LedON >= numOfRegisterPins){
      AllLEDOFF(5);
    }
  }
}

void BelenStarOFFrestONsecuencial1by1(unsigned long delayedtime,unsigned long runningtime){
    
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
// AllLEDOFF(5);
  while (runningtime >= t_actualizado - tiempo) {
    int LedON = 0;
    while (LedON <= numOfRegisterPins) {
      for(int i = numOfRegisterPins - 1; i >=  0; i--){
         if (i > MAXPINSTARSKY){
          setRegisterPin(i,LOW);
         } else {
           if (i == LedON){
             setRegisterPin(i,HIGH); 
           } else {
             setRegisterPin(i,LOW); 
           }
         }
      }
    writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
    PersonalDelay(delayedtime);
    t_actualizado = millis();
    LedON++;
    }
  }
}

void BelenStarsecuencial1by1andskyOFF(unsigned long delayedtime,unsigned long runningtime){
  
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
 // AllLEDOFF(5);
  while (runningtime >= t_actualizado - tiempo) {
    int LedON = 0;
    while (LedON <= numOfRegisterPins) {
      for(int i = numOfRegisterPins - 1; i >=  0; i--){
         if (i <= MAXPINSTARSKY){
          setRegisterPin(i,LOW);
         } else {
           if (i == LedON){
             setRegisterPin(i,HIGH); 
           } else {
             setRegisterPin(i,LOW); 
           }
         }
      }
    writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
    PersonalDelay(delayedtime);
    t_actualizado = millis();
    LedON++;
    }
  }
}

void RandomBlinkSkyStarandEBONandOFF (unsigned long delayedtime,unsigned long runningtime){
  
  byte z = 0;
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
 // AllLEDOFF(5);
  while (runningtime >= t_actualizado - tiempo) {
    for(int i = numOfRegisterPins - 1; i >=  0; i--){
       if (i <= MAXPINSTARSKY){
        setRegisterPin(i,random(2));
       } else {
        setRegisterPin(i,z);
       }
    }
    z = !z;
    writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
    PersonalDelay(delayedtime);
    t_actualizado = millis();
  }
}

void AllRandom(unsigned long delayedtime,unsigned long runningtime){
  
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
//  AllLEDOFF(5);
  while (runningtime >= t_actualizado - tiempo) {
    for(int i = numOfRegisterPins - 1; i >=  0; i--){
       setRegisterPin(i,random(2));
    }
    writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
    PersonalDelay(delayedtime);
    t_actualizado = millis();
  }  
}

void BelenStarONrstOFF(unsigned long delayedtime,unsigned long runningtime){

  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
//  AllLEDOFF(5);
  while (runningtime >= t_actualizado - tiempo) {
    for(int i = numOfRegisterPins - 1; i >=  0; i--){
       if (i <= MAXPINSTARSKY){
        setRegisterPin(i,LOW);
       } else {
        setRegisterPin(i,HIGH);
       }
    }
    writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
    PersonalDelay(delayedtime);
    t_actualizado = millis();
  }
}

void BelenStarOFFrestON(unsigned long delayedtime,unsigned long runningtime){
  
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
  int bcontrol = 0;
  AllLEDOFF(5);
  while (runningtime >= t_actualizado - tiempo) {
    //for(int i = 13 - 1; i >=  0; i--){
    if (bcontrol == 0) {
      for(int i = numOfRegisterPins - 1; i >=  0; i--){
         if (i <= MAXPINSTARSKY){
          setRegisterPin(i,HIGH);
         } else {
          setRegisterPin(i,LOW);
         }
         bcontrol = 1;
    }
    writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
    }
    PersonalDelay(delayedtime);
    t_actualizado = millis();
  }
}

void PersonalDelay(unsigned long delayed){
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis();
//AllLEDOFF(5);
  while (delayed >= t_actualizado - tiempo) {
    t_actualizado = millis();
  }
}

void AllLEDON(unsigned long delayed){
  
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis();
//  AllLEDOFF(5);
  while (delayed >= t_actualizado - tiempo) {
    for(int i = numOfRegisterPins - 1; i >=  0; i--){
       setRegisterPin(i,HIGH);
    }
    writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
    t_actualizado = millis();
  }
}

void AllLEDOFF(unsigned long delayed){
  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis();
 // AllLEDOFF(5);
  while (delayed >= t_actualizado - tiempo) {
    for(int i = numOfRegisterPins - 1; i >=  0; i--){
       setRegisterPin(i,LOW);
    }
    writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
    t_actualizado = millis();
  }
}


void SecuencialLED1by1(unsigned long delayedtime,unsigned long runningtime){

  unsigned long tiempo = millis();
  unsigned long t_actualizado = millis(); 
//  AllLEDOFF(5);
  while (runningtime >= t_actualizado - tiempo) {
    int LedON = 0;
    while (LedON <= numOfRegisterPins) {
      for(int i = numOfRegisterPins - 1; i >=  0; i--){
         if (i == LedON){
          setRegisterPin(i,HIGH); 
         } else {
          setRegisterPin(i,LOW); 
         }
      }
      writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
      PersonalDelay(delayedtime);
      t_actualizado = millis();
      LedON++;
    }
  }
}

void AllEffectSencuencial(){
      SecuencialLED1by1(50,5000);    
      RandomBlinkSkyStarandEBONandOFF(250,5000);
      AllLEDOFF(5000);
      AllLEDON(5000);
      BelenStarONrstOFF(50,5000);
      BelenStarOFFrestON(50,5000);
      AllRandom(250,7000);
      BelenStarsecuencial1by1andskyOFF(50,5000);
      BelenStarOFFrestONsecuencial1by1(50,5000);
      AllLEDON1by1(50,5000);//parpadeo
      BelenStarON1by1(50,5000);
      AllONandOff1by1(50,5000);
      OFF1by1Secuencial(250,5000);
      BelenStarOFF1by1restOFF(250,5000);
      ALLONandbelenstaroff1by1(150,5000);
      ALLblinking(5000);
      BlastbyoffsetinBELENstar(80,5000,random(1,3));
}
void loop(){
  if (bulean == 0){
    AllEffectSencuencial(); 
    bulean = 1;
  }
  int iEfecto = random(NUMEFECTOS);
  ApplyEfecto(iEfecto);  
}
