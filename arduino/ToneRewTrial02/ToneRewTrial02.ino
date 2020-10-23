#include "global_variables.h"

String version = "#Ard_TonRew.1.20200505.0";
/// Only Start function is useable

String versionPyt = "";
int command = 0;
int value = 0;

void setup() {
  Serial.begin(115200);
  if(Serial.available()>0){
    versionPyt = Serial.readStringUntil('\n');
  }
  Serial.print("Version: "); Serial.println(version);
  pinMode(TonePin,OUTPUT);
  pinMode(RwPin,OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  /*
  if(Serial.available()>0){
    command = Serial.read();
    if(command=='s') state = 'A';
    value = Serial.read();
    if(command==0) TF = value;
    if(command==1) TT = value;
    if(command==2)  g = value;
    if(command==3) RwT = value;
    if(command==4) iT = value;
    if(command==5) dif = value;
    if(command==6) nT = value;
  }
  */
  if(state=='A'){
    Serial.println("\nNew set of trials");
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
    //Serial.println("End of the training\n\n");
    state = 'D';
    }
  else if(state=='D'){
    if(Serial.available()>0){
      //Serial.println(Serial.readStringUntil('\n'));
      if(Serial.read()=='s'){
        state = 'A';
        //Serial.print("State: "); Serial.println(state);
      }
    }
  }
  //Update parameters
  //if(Serial.available()>0){}
}

void doTrial(){
  if(Timer(aTime,TT,bTT))       Tone();
  if(Timer(aTime,g,bg))         gap();
  if(Timer(aTime,RwT,bRwT))     Reward();
  if(Timer(aTime,iT*1000,biT))  interTrials();
  if(Timer(aTime,0,newT))       newTrial();
}
