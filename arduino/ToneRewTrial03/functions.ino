bool Timer(unsigned long& start,int wait,bool first){
  if(millis()-zTime>start && first){
    start += wait;
    return true;
  }
  else {
    return false;
  }
}

//---Functions of doTrial------------------------
void Tone(){
  //Serial.print("Ttrail ");
  //Serial.println(aT+1);
  digitalWrite(TonePin,HIGH);
  tone(PiezoPin,parVal[0],parVal[1]);
  //Serial.println("TONE! TONE! TONE!");
  bTT = false;
  bg = true;
}

void gap(){
  digitalWrite(TonePin,LOW);
  //Serial.println("------------------------");
  bg = false;
  bRwT = true;
}

void Reward(){
  digitalWrite(RwPin,HIGH);
  //Serial.println("Reward!!!!!!!!!!!!!");
  bRwT = false;
  biT = true;
}

void interTrials(){
  digitalWrite(RwPin,LOW);
  randT = random(-parVal[5],parVal[5]+1)*1000;
  aTime += randT;
  //Serial.print("InterTrail time: ");
  //Serial.print((randT+iT*1000)/1000);
  biT = false;
  newT = true;
  //Serial.println("s\tSilence!!!");
}

void newTrial(){
  aT += 1;
  newT = false;
  bTT = true;
  zTime = millis();
  aTime = 0;
  if(aT>=parVal[6]){
    state = 'C';
    //--for Arduino start comm. 
    /*
    command = 8;
    value.integer = parVal[6];
    Serial.write(command);
    Serial.write(value.array[0]);
    Serial.write(value.array[1]);
    command = 0;
    value.integer = 0;
    */
  }
}

//---Functions of communication-----
void readOrder(){
  if(Serial.available()>0){
    command = Serial.read();
    ORDER = true;
    Serial.write(command);
    serDelay = millis();
  }
}

void readValue(){
  if(Serial.available()>1){
    value.array[0] = Serial.read();
    value.array[1] = Serial.read();
    ORDER = false;
    Serial.write(value.array[0]);
    Serial.write(value.array[1]);
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
