bool Timer(unsigned long& start,int wait,bool first){
  if(millis()-zTime>start && first){
    start += wait;
    return true;
  }
  else {
    return false;
  }
}

void Tone(){
  //Serial.print("Ttrail ");
  //Serial.println(aT+1);
  digitalWrite(TonePin,HIGH);
  tone(PiezoPin,TF,TT);
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
  randT = random(-dif,dif+1)*1000;
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
  if(aT==nT) state = 'C';
}
