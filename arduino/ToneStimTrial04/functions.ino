//---Control functions--------------------
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

void stateChanger(byte n,char whereto){
  if((command==n) && !ORDER){
    command = NOTHING;
    value.integer = 0;
    state = whereto;
    if(n==STOP){
      trialCounter = 0;
      writeOrderValue(STOP,0);
    }
    if(n==RESET){
      chosenStimulus = 0;
      writeOrderValue(RESET,0);
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
  if(parVal[chosenStimulus-1+REWARD_L-N_ORDERS]==0){
    digitalWrite(StimPin[chosenStimulus],HIGH);
    delay(2);
    digitalWrite(StimPin[chosenStimulus],LOW);
    delay(98);
    digitalWrite(StimPin[chosenStimulus],HIGH);
    delay(2);
    digitalWrite(StimPin[chosenStimulus],LOW);
  }
  else digitalWrite(StimPin[chosenStimulus],HIGH);
  aS[chosenStimulus-1]++;
  writeOrderValue(chosenStimulus-1+A_N_Rews,aS[chosenStimulus-1]); //OK
  writeOrderValue(DIGITAL_IN,digitalRead(digitalIn));
  writeOrderValue(ANALOG_IN,analogRead(analogIn));
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

void testPins(){
  if(debug){
    for(int pin=0;pin<N_STIM+1;pin++){
      digitalWrite(StimPin[pin],HIGH);
      delay(250);
      digitalWrite(StimPin[pin],LOW);
    }
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
      if(i==chosenStimulus-1) stimuli[i+1]--;
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
