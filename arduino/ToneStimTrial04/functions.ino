//---Control functions--------------------
void stateChanged(byte n,char whereto){
  if((command==n) && !ORDER){
    command = NOTHING;
    value.integer = 0;
    state = whereto;
    if(n==STOP){
      trialCounter = 0;
      //aT++;
    }
  }
}

void stepper(unsigned int duration){
  nextStepTimer.setTimeOutTime(duration);
  if(trialCounter==3) writeOrderValue(T_INTER_TRIAL,duration); //OK
  nextStepTimer.reset();
  trialCounter++;
  if(trialCounter>4) trialCounter = 0;
}

void stimulusChooser(){
  while(chosenStimulus==0){
    randomSeed(analogRead(0));
    byte r = 1+random(N_STIM);
    if(stimuli[r]>0){
      chosenStimulus = r;
      stimuli[r]--;
    }
  }
}

bool ended(){
  bool e = true;
  for(int i=0;i<N_STIM;i++){
    //if(aS[i]<parVal[i]) e = false;
    if(stimuli[i+1]>0) e = false;
  }
  return e;
}

//---Functions of doTrial-----------------
void Tone(){
  digitalWrite(StimPin[TONE_IMIT],HIGH);
  tone(PiezoPin,parVal[chosenStimulus+3],parVal[TONE_TIME-N_ORDERS]);
  stepper(parVal[TONE_TIME-N_ORDERS]);
}

void gap(){
  digitalWrite(StimPin[TONE_IMIT],LOW);
  stepper(parVal[GAP-N_ORDERS]);
}

void Stimulus(){
  stepper(parVal[chosenStimulus-1+N_ORDERS]);
  if(chosenStimulus==TAIL_SHOCK){
    digitalWrite(StimPin[TAIL_SHOCK],HIGH);
    delay(2);
    digitalWrite(StimPin[TAIL_SHOCK],LOW);
    delay(98);
    digitalWrite(StimPin[TAIL_SHOCK],HIGH);
    delay(2);
    digitalWrite(StimPin[TAIL_SHOCK],LOW);
  }
  else digitalWrite(StimPin[chosenStimulus],HIGH);
  aS[chosenStimulus-1]++;
  writeOrderValue(chosenStimulus-1+A_N_Rews,aS[chosenStimulus-1]); //OK
}

void interTrials(){
  for(int i=0;i<N_STIM;i++){
    digitalWrite(StimPin[i+1],LOW);
  }
  long D = parVal[DIFFUSION_F-N_ORDERS];
  //randomSeed(analogRead(0));
  int randT = random(-D,D+1);
  stepper((parVal[T_INTER_TRIAL-N_ORDERS]+randT)*1000);
}

void newTrial(){
  chosenStimulus = 0;
  if(ended()){
    state = 'C';
    writeOrderValue(END_TRS,0); //OK
  }
  else{
    stimulusChooser();
  }
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
  Serial.write(ARD_SEND);
  Serial.write(toPyt.array,2);
  toPyt.integer = Val;
  Serial.write(Com);
  Serial.write(toPyt.array,2);
  toPyt.integer = 0;
}

void readOut(){
  while(Serial.available()>0){
    char t = Serial.read();
  }
}

//---Updating functions-------------------
void updateModifier(unsigned int mod){
  impulse = mod;
  for(int i=0;i<N_STIM;i++){
    stimuli[i+1] = 0;
    if(bitRead(impulse,i)==1){
      if(parVal[i]-aS[i]>=0) stimuli[i+1] = parVal[i]-aS[i];
      else stimuli[i+1] = 0;
      writeOrderValue(i+N_ORDERS,parVal[i]);  //OK -
    }
    else writeOrderValue(i+N_ORDERS,0);
  }
  command = 0;
  value.integer = 0;
}

void updateParameter(){
  parVal[command-N_ORDERS] = value.integer;
  if(command-N_ORDERS<N_STIM){
    updateModifier(impulse);
  }
  command = 0;
  value.integer = 0;
}
