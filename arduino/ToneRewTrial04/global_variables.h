/*
	global_variable.h - Library for TonRewTrial
	Created by Gaspar J. Schliszka
*/

//---Pin variables------------------
const byte  TonePin = 8; //RED
const byte    RwPin = 7; //GREEN
const byte PiezoPin = 9; //buzzer

//---Initial state------------------
char state = 'C';

//---Timer variables----------------
unsigned long  zTime = 0;   //start time of training ~zeroTime (in ms)
unsigned long  aTime = 0;   //actualTime in doTrail()
          int  randT = 0;   //iT+random(-dif,dif+1)
          int     aT = 0;   //number of actualTrial
unsigned long serDelay = 0; //delay between order and value reading

//---Additional timer variabels-----
bool  bTT = false;
bool   bg = false;
bool bRwT = false;
bool  biT = false;
bool newT = false;

//---Parameters of the Trials-------
unsigned int  TF = 100;    //0:ToneFrequency
unsigned int  TL = 1000;   //1:ToneLength
unsigned int  GL = 1000;   //2:GapLength
unsigned int RwL = 250;    //3:RewardLength
unsigned int  iT = 5;      //4:time interTrials (in s)
unsigned int dif = 1;      //5:diffusion factor for random iT component
unsigned int  nT = 3;      //6:number of Trials
unsigned int parVal[] = {TF,TL,GL,RwL,iT,dif,nT};

//---Union for bytes-integers------
union ArrayToInt{
  byte array[2];
  unsigned int integer;
};

//---Communicational variables-----
byte command = 0;
ArrayToInt value;
bool ORDER = false;
