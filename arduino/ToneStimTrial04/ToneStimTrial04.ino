#include "global_variables.h"
#include "order.h"

String version = "#Ard_TonStim.4.20201110.2";

void setup() {
  Serial.begin(115200);
  readOut();
  Serial.print(version);
  readOut();
  delay(1000);
  //delay(valami);
  //delay(NOTHING);
  //pinMode(TonePin,OUTPUT);
  for(int i=0;i<5;i++) pinMode(StimPin[i],OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  if(!ORDER) readOrder();
  if(ORDER && nextReadTimer.hasTimedOut()) readValue();
  if((command>9) && !ORDER) updateParameter();
  if((command==MODIFIER) && !ORDER) updateModifier(value.integer);
  if(Serial.available()>2) readOut();

  if(state=='A'){ //START state
    for(int i=0;i<4;i++){ //Not necessary
      //tone(PiezoPin,40,250);
      digitalWrite(StimPin[TONE_IMIT],HIGH);
      delay(250);
      digitalWrite(StimPin[TONE_IMIT],LOW);
      digitalWrite(StimPin[REWARD],HIGH);
      delay(250);
      digitalWrite(StimPin[REWARD],LOW);
    }
    state = 'B';
    aT = 0;
    trialCounter = 0;
    updateModifier(impulse);
    stimulusChooser();
    nextStepTimer.setTimeOutTime(0);
    nextStepTimer.reset();
  }
  else if(state=='B'){ //TO DO state
    doTrial();
    stateChanged(START,'B');
    stateChanged(STOP,'D');
    stateChanged(RESET,'C');
  }
  else if(state=='C'){ //Standby state
    stateChanged(START,'A');
  }
  else if(state=='D'){ //STOP state
    stateChanged(START,'B');
    stateChanged(RESET,'C');
  }
}

void doTrial(){
  if(nextStepTimer.hasTimedOut() && trialCounter==0)        Tone();
  if(nextStepTimer.hasTimedOut() && trialCounter==1)         gap();
  if(nextStepTimer.hasTimedOut() && trialCounter==2)    Stimulus();
  if(nextStepTimer.hasTimedOut() && trialCounter==3) interTrials();
  if(nextStepTimer.hasTimedOut() && trialCounter==4)    newTrial();
}
