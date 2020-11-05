/*
	global_variable.h - Library for TonStimTrial
	Created by Gaspar J. Schliszka
*/
#include <SoftTimers.h>

//---Pin variables------------------
const byte  TonePin = 8; //RED
const byte    RwPin = 7; //GREEN
const byte PiezoPin = 9; //buzzer

//---Initial state------------------
char state = 'C';

//---Timer variables----------------
SoftTimer nextStepTimer;
SoftTimer nextReadTimer;
     int  aT = 0;   //number of actualTrial
     byte trialCounter = 0; //along one trial
unsigned long serDelay = 100; //delay between order and value reading

//---Parameters of the Trials-------
unsigned int  FR = 400;    //0:ToneFrequency for Reward
unsigned int  FA = 100;    //1:ToneFrequency for Air puff
unsigned int  FT = 100;    //2:ToneFrequency for Tail shock
unsigned int  FC = 100;    //3:ToneFrequency for Conditioner
unsigned int  TL = 1000;   //4:ToneLength
unsigned int  GL = 1000;   //5:GapLength
unsigned int RwL = 250;    //6:RewardLength
unsigned int  iT = 5;      //7:time interTrials (in s)
unsigned int dif = 1;      //8:diffusion factor for random iT component
unsigned int  nT = 3;      //9:number of Trials
unsigned int parVal[] = {FR,FA,FT,FC,TL,GL,RwL,iT,dif,nT};
unsigned int impulse = 1;  //binary code for stimuli
unsigned int stimuli[] = {nT,0,0,0};

//---Union for bytes-integers------
union ArrayToInt{
  byte array[2];
  unsigned int integer;
};

//---Communicational variables-----
byte command = 0;
ArrayToInt value;
bool ORDER = false;
