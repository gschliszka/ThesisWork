//---Control functions--------------------
void stateChanged(byte n,char whereto){
  if((command==n) && !ORDER){
    command = NOTHING;
    value.integer = 0;
    state = whereto;
    if(n==STOP){
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
    byte r = 1+random(N_STIM);
    if(stimuli[r]>0){
      chosenStimulus = r;
      stimuli[r]--;
    }
  }
}

//---Functions of doTrial-----------------
void Tone(){
  digitalWrite(StimPin[TONE_IMIT],HIGH);
  tone(PiezoPin,parVal[chosenStimulus],parVal[TONE_TIME-N_ORDERS]);
  writeOrderValue(ACTUAL_N,aT+1);
  stepper(parVal[TONE_TIME-N_ORDERS]);
}

void gap(){
  digitalWrite(StimPin[TONE_IMIT],LOW);
  stepper(parVal[GAP-N_ORDERS]);
}

void Stimulus(){
  stepper(parVal[chosenStimulus+6]);
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
}

void interTrials(){
  for(int i=0;i<N_STIM;i++){
    digitalWrite(StimPin[i+1],LOW);
  }
  chosenStimulus = 0;
  int randT = random(-parVal[DIFFUSION_F-N_ORDERS],parVal[DIFFUSION_F-N_ORDERS]+1);
  stepper((parVal[T_INTER_TRIAL-N_ORDERS]+randT)*1000);
}

void newTrial(){
  aT++;
  if(aT>=nT){
    state = 'C';
    writeOrderValue(END_TRS,0);
  }
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
  for(int i=0;i<N_STIM;i++){
    stimuli[i+1] = 0;
    if(bitRead(impulse,i)==1){
      stimuli[i+1] = parVal[N_OF_TRS-N_ORDERS]-aT; //Source of errors!: if aT > parVal[0], stimuli[i] < 0
      nT += stimuli[i+1];
    }
  }
  writeOrderValue(TRIAL_N,nT);
  aT = 0;
  command = 0;
  value.integer = 0;
}

void updateParameter(){
  parVal[command-N_ORDERS] = value.integer;
  command = 0;
  value.integer = 0;
}

void readOut(){
  while(Serial.available()>0){
        char t = Serial.read();
      }
}
