#include <C:\Users\schga\OneDrive\Dokumentumok\GitHub\ThesisWork\arduino\ToneRewTrial03\global_variables.h>

String version = "#Ard_CommProt.0.20201027";

void setup() {
  Serial.begin(115200);
  Serial.print(version);
}

void loop() {
}
