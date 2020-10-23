#include "global_variables.h"

String version = "#Ard_TonRew.0.20200427.1";
/// No Python communication
String versionPyt = "";

void setup() {
  Serial.begin(115200);
  if(Serial.available()>0){
    versionPyt = Serial.readStringUntil('\n');
  }
  Serial.print("Version: "); Serial.println(version);
  Serial.println("Setup");
  pinMode(TonePin,OUTPUT);
  pinMode(RwPin,OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
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
    Serial.println("End of the training\n\n");
    TF = 200;
    state = 'D';
    }
  else if(state=='D'){
    if(Serial.available()>0){
      //Serial.println(Serial.readStringUntil('\n'));
      if(Serial.readStringUntil('\n')=="Start"){
        state = 'A';
        Serial.print("State: ");
        Serial.println(state);
        /*bg = false;
        bRwT = false;
        biT = false;
        newT = false;*/
      }
    }
  }
}

void doTrial(){
  if(Timer(aTime,TT,bTT))       Tone();
  if(Timer(aTime,g,bg))         gap();
  if(Timer(aTime,RwT,bRwT))     Reward();
  if(Timer(aTime,iT*1000,biT))  interTrials();
  if(Timer(aTime,0,newT))       newTrial();
}
