#include <C:\Users\schga\OneDrive\Dokumentumok\GitHub\ThesisWork\arduino\ToneRewTrial03\global_variables.h>

String version = "#Ard_CommProt.0.20201027";

void setup() {
  Serial.begin(115200);
  Serial.print(version);
}

void loop() {
}

oid readOrder(){
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
