void stateChanged(byte word,char whereto){
  if((command==word) && !ORDER){
    command = 0;
    value.integer = 0;
    state = whereto;
  }
}

//---Functions of doTrial------------------------
void Tone(){
  //Serial.print("Ttrail ");
  //Serial.println(aT+1);
  digitalWrite(TonePin,HIGH);
  tone(PiezoPin,parVal[0],parVal[1]);
  trialCounter++;                           //All of them into one function
  nextStepTimer.setTimeOutTime(parVal[1]);  //
  nextStepTimer.reset();                    //
}

void gap(){
  digitalWrite(TonePin,LOW);
  //Serial.println("------------------------");
  trialCounter++;
  nextStepTimer.setTimeOutTime(parVal[2]);
  nextStepTimer.reset();
}

void Reward(){
  digitalWrite(RwPin,HIGH);
  //Serial.println("Reward!!!!!!!!!!!!!");
  trialCounter++;
  nextStepTimer.setTimeOutTime(parVal[3]);
  nextStepTimer.reset();
}

void interTrials(){
  digitalWrite(RwPin,LOW);
  int randT = random(-parVal[5],parVal[5]+1);
  trialCounter++;
  nextStepTimer.setTimeOutTime((parVal[4]+randT)*1000);
  nextStepTimer.reset();
  //Serial.print("InterTrail time: ");
  //Serial.print((randT+iT*1000)/1000);
  //Serial.println("s\tSilence!!!");
}

void newTrial(){
  aT += 1;
  if(aT>=parVal[6]) state = 'C';
  trialCounter = 0;
  nextStepTimer.setTimeOutTime(0);
  nextStepTimer.reset();
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
    //value.array[0] = Serial.read();
    //value.array[1] = Serial.read();
    ORDER = false;
    Serial.write(value.array,2);
    //Serial.write(value.array[0]);
    //Serial.write(value.array[1]);
  }
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
