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
    stateChanger(START,'B');
    stateChanger(STOP,'D');
    stateChanger(RESET,'C');
  }
  else if(state=='C'){ //Idle state
    stateChanger(START,'A');
  }
  else if(state=='D'){ //STOP state
    stateChanger(START,'B');
    stateChanger(RESET,'C');
  }
}
