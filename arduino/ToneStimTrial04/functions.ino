void stateChanged(byte n,char whereto){
  if((command==n) && !ORDER){
    command = 0;
    value.integer = 0;
    state = whereto;
    if(n==3){
      trialCounter = 0;
      aT++;
    }
  }
}

void stepper(unsigned int duration){
  trialCounter++;
  nextStepTimer.setTimeOutTime(duration);
  nextStepTimer.reset();
  if(trialCounter>4) trialCounter = 0;
}

//---Functions of doTrial------------------------
void Tone(){
  //Serial.print("Ttrail ");
  //Serial.println(aT+1);
  digitalWrite(TonePin,HIGH);
  tone(PiezoPin,parVal[0],parVal[4]);
  stepper(parVal[4]);
}

void gap(){
  digitalWrite(TonePin,LOW);
  stepper(parVal[5]);
}

void Stimulus(){
  digitalWrite(RwPin,HIGH);
  stepper(parVal[6]);
}

void interTrials(){
  digitalWrite(RwPin,LOW);
  int randT = random(-parVal[8],parVal[8]+1);
  stepper((parVal[7]+randT)*1000);
}

void newTrial(){
  aT++;
  if(aT>=nT) state = 'C';
  stepper(0);
}

//---Functions of communication-----
void readOrder(){
  if(Serial.available()>0){
    command = Serial.read();
    ORDER = true;
    Serial.write(command);
    nextReadTimer.setTimeOutTime(serDelay);
    nextReadTimer.reset();
  }
}

void readValue(){
  if(Serial.available()>1){
    Serial.readBytes(value.array,2);
    ORDER = false;
    Serial.write(value.array,2);
  }
}

void updateModifier(){
  impulse = value.integer;
  nT = 0;
  for(int i=0;i<4;i++){
    if(bitRead(impulse,i)==1){
      stimuli[i] = parVal[9];
      nT += stimuli[i];
    }
  }
  aT = 0;
  command = 0;
  value.integer = 0;
}

void updateParameter(){
  parVal[command-10] = value.integer;
  command = 0;
  value.integer = 0;
}

void readOut(){
  while(Serial.available()>0){
        char t = Serial.read();
      }
}
