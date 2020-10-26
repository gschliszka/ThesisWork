#include "global_variables.h"
#include "order.h"

String version = "#Ard_TonRew.3.20200528.3";
/// Only Start function is useable

String versionPyt = "";

void setup() {
  Serial.begin(115200);
  /*
  while(Serial.available()<1){} // <-- 
  
  if(Serial.available()>0){
    versionPyt = Serial.readStringUntil('\n');
  }*/
  
  //Serial.print("Version: ");
  Serial.println(version);
  
  pinMode(TonePin,OUTPUT);
  pinMode(RwPin,OUTPUT);
  randomSeed(analogRead(0));
  
  value.integer = 0;
  readOut();
}

void loop() {
  if(!ORDER) readOrder();
  if(ORDER && (millis()-serDelay)>100) readValue();
  if((command>9) && !ORDER) updateParameter();
  if(Serial.available()>3) readOut();
  
  if(state=='A'){
    //Serial.println("\nNew set of trials");
    
    for(int i=0;i<4;i++){
      //tone(PiezoPin,40,250);
      digitalWrite(TonePin,HIGH);
      delay(250);
      digitalWrite(TonePin,LOW);
      digitalWrite(RwPin,HIGH);
      delay(250);
      digitalWrite(RwPin,LOW);
    }
    
    zTime = millis();
    aTime = 0;
    state = 'B';
    aT = 0;
    bTT = true;
  }
  else if(state=='B'){
    doTrial();
  }
  else if(state=='C'){
    if((command==2) && !ORDER){
      command = 0;
      value.integer = 0;
      state = 'A';
    }
  }
}

void doTrial(){
  if(Timer(aTime,parVal[1],bTT))       Tone();
  if(Timer(aTime,parVal[2],bg))         gap();
  if(Timer(aTime,parVal[3],bRwT))     Reward();
  if(Timer(aTime,parVal[4]*1000,biT))  interTrials();
  if(Timer(aTime,0,newT))       newTrial();
}
