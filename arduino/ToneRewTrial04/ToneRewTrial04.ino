#include "global_variables.h"
//#include <SoftTimers.h>

String version = "#Ard_TonStim.4.20201102.0";


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

  if(state=='A'){ //START state
    for(int i=0;i<4;i++){
      //tone(PiezoPin,40,250);
      digitalWrite(TonePin,HIGH);
      delay(250);
      digitalWrite(TonePin,LOW);
      digitalWrite(RwPin,HIGH);
      delay(250);
      digitalWrite(RwPin,LOW);
    }
    
    state = 'B';
    aT = 0;
    trialCounter = 0;
    nextStepTimer.setTimeOutTime(0);
    nextStepTimer.reset();
  }
  else if(state=='B'){ //TO DO state
    doTrial();
    stateChanged(3,'D');
    stateChanged(4,'C');
  }
  else if(state=='C'){ //Standby state
    stateChanged(2,'A');
  }
  else if(state=='D'){ //PAUSE state
    stateChanged(2,'B');
    stateChanged(4,'C');
  }
}

void doTrial(){
  if(nextStepTimer.hasTimedOut() && trialCounter==0)        Tone();
  if(nextStepTimer.hasTimedOut() && trialCounter==1)         gap();
  if(nextStepTimer.hasTimedOut() && trialCounter==2)      Reward();
  if(nextStepTimer.hasTimedOut() && trialCounter==3) interTrials();
  if(nextStepTimer.hasTimedOut() && trialCounter==4)    newTrial();
}
