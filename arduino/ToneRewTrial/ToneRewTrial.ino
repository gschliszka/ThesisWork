String version = "#Ard_TonRew.0.20200411.0";
/// No Python communication

const int  TonePin = 8; //RED
const int    RwPin = 7; //GREEN
const int PiezoPin = 9; //buzzer

char state = 'A';

int  zTime = 0;   //start time of training ~zeroTime (in ms)
int  aTime = 0;   //actualTime in doTrail()
int  randT = 0;   //iT+random(-dif,dif+1)
int     aT = 0;   //number of actualTrial

int  TF = 100;    //ToneFrequency
int  TT = 1000;   //ToneTime
int   g = 1000;   //gap
int RwT = 250;    //RewardTime
int  iT = 10;      //time interTrials (in s)
int dif = 5;      //diffusion factor for random iT component
int  nT = 3;      //number of Trials

bool  bTT = false;
bool   bg = false;
bool bRwT = false;
bool  biT = false;
bool newT = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup");
  Serial.print("Version: "); Serial.println(version);
  pinMode(TonePin,OUTPUT);
  pinMode(RwPin,OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  if(state=='A'){
    Serial.println("\nNew set of trials");
    for(int i=0;i<4;i++){
      //tone(PiezoPin,40,250);
      digitalWrite(TonePin,HIGH);
      delay(250);
      digitalWrite(TonePin,LOW);
      digitalWrite(RwPin,HIGH);
      delay(250);
      digitalWrite(RwPin,LOW);
    }
    zTime = millis();
    aTime = 0;
    state = 'B';
    aT = 0;
    bTT = true;
  }
  else if(state=='B'){
    doTrial();
  }
  else if(state=='C'){
    Serial.println("End of the training\n\n");
    state = 'D';
  }
}

void doTrial(){
  if(Timer(aTime,TT,bTT))       Tone();
  if(Timer(aTime,g,bg))         gap();
  if(Timer(aTime,RwT,bRwT))     Reward();
  if(Timer(aTime,iT*1000,biT))  interTrials();
  if(Timer(aTime,0,newT))       newTrial();
}
