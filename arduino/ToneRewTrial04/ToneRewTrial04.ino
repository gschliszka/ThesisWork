#include "global_variables.h"
#include <SoftTimers.h>

String version = "#Ard_TonStim.4.20201102.0";
SoftTimer nextStepTimer;

void setup() {
  Serial.begin(115200);
  readOut();
  Serial.print(version);
  readOut();
  delay(1000);
  pinMode(TonePin,OUTPUT);
  pinMode(RwPin,OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  if(!ORDER) readOrder();
  if(ORDER && (millis()-serDelay)>100) readValue();
  if((command>9) && !ORDER) updateParameter();
  if(Serial.available()>2) readOut();

  if(state=='A'){
    
  }
  else if(state=='B'){
    doTrial();
  }
  else if(state=='C'){
    if((command==2) && !ORDER){
      command = 0;
      value.integer = 0;
      zTime = millis();
      aTime = 0;
      state = 'B';
      aT = 0;
      nextStepTimer.setTimeOutTime(TL);
      nextStepTimer.reset();
    }
  }
}

void doTrial(){
  
}
