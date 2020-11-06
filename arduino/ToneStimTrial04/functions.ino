//---Control functions--------------------
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

void stimulusChooser(){
  while(chosenStimulus==0){
    byte r = random(4);
    if(stimuli[r]>0){
      chosenStimulus = r+1;
      stimuli[r]--;
    }
  }
}

//---Functions of doTrial-----------------
void Tone(){
  digitalWrite(TonePin,HIGH);
  tone(PiezoPin,parVal[chosenStimulus],parVal[5]);
  writeOrderValue(5,aT+1);
  stepper(parVal[5]);
}

void gap(){
  digitalWrite(TonePin,LOW);
  stepper(parVal[6]);
}

void Stimulus(){
  stepper(parVal[chosenStimulus+6]);
  if(chosenStimulus==3){
    digitalWrite(StimPin[2],HIGH);
    delay(2);
    digitalWrite(StimPin[2],LOW);
    delay(98);
    digitalWrite(StimPin[2],HIGH);
    delay(2);
    digitalWrite(StimPin[2],LOW);
  }
  else digitalWrite(StimPin[chosenStimulus-1],HIGH);
}

void interTrials(){
  for(int i=0;i<4;i++){
    digitalWrite(StimPin[i],LOW);
  }
  chosenStimulus = 0;
  int randT = random(-parVal[12],parVal[12]+1);
  stepper((parVal[11]+randT)*1000);
}

void newTrial(){
  aT++;
  if(aT>=nT) state = 'C';
  else stimulusChooser();
  stepper(0);
}

//---Functions of communication-----------
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

void writeOrderValue(byte Com, unsigned int Val){
  toPyt.integer = Val;
  Serial.write(Com);
  Serial.write(toPyt.array,2);
  toPyt.integer = 0;
}

void updateModifier(int mod){
  impulse = mod;
  nT = 0;
  for(int i=0;i<4;i++){
    if(bitRead(impulse,i)==1){
      stimuli[i] = 0;
      stimuli[i] = parVal[0]-aT;
      nT += stimuli[i];
    }
  }
  writeOrderValue(6,nT);
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
