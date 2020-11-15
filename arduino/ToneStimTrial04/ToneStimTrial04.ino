#include "global_variables.h"
#include "order.h"

String version = "#Ard_TonStim.4.20201111.3";

void setup(){
  Serial.begin(115200);
  readOut();
  Serial.print(version);
  readOut();
  delay(1000);

  for(int i=0;i<5;i++) pinMode(StimPin[i],OUTPUT);
  randomSeed(analogRead(0));
  pinMode(analogIn,INPUT);
  pinMode(digitalIn,INPUT);
}

void loop() {
  if(!ORDER) readOrder();
  if(ORDER && nextReadTimer.hasTimedOut()) readValue();
  if((command>9) && !ORDER) updateParameter();
  if((command==MODIFIER) && !ORDER) updateModifier(value.integer); //OK
  if(Serial.available()>2) readOut();

  if(state=='A'){ //START state
    testPins();
    doStarterReduction();
  }
  else if(state=='B'){ //TO DO state
    doTrial();
    stateChanged(START,'B');
    stateChanged(STOP,'D');
    stateChanged(RESET,'C');
  }
  else if(state=='C'){ //Idle state
    stateChanged(START,'A');
  }
  else if(state=='D'){ //STOP state
    stateChanged(START,'B');
    stateChanged(RESET,'C');
  }
}

void testPins(){
  if(debug){
    for(int pin=0;pin<N_STIM+1;pin++){
      digitalWrite(StimPin[pin],HIGH);
      delay(250);
      digitalWrite(StimPin[pin],LOW);
    }
  }
}

void doStarterReduction(){
  state = 'B';
  for(int i=0;i<N_STIM;i++){
    aS[i] = 0;
    writeOrderValue(i+A_N_Rews,aS[i]); //OK
  }
  updateModifier(impulse); // OK - in state 'A'
  stimulusChooser();
  trialCounter = 0;
  nextStepTimer.setTimeOutTime(0);
  nextStepTimer.reset();
}
void doTrial(){
  if(nextStepTimer.hasTimedOut() && trialCounter==0)        Tone();
  if(nextStepTimer.hasTimedOut() && trialCounter==1)         gap();
  if(nextStepTimer.hasTimedOut() && trialCounter==2)    Stimulus();
  if(nextStepTimer.hasTimedOut() && trialCounter==3) interTrials();
  if(nextStepTimer.hasTimedOut() && trialCounter==4)    newTrial();
}
