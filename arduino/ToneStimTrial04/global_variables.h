/*
	global_variable.h - Library for TonStimTrial
	Created by Gaspar J. Schliszka
*/
#include <SoftTimers.h>

//---Pin variables------------------
const byte  PiezoPin = 9; //buzzer
const byte   TonePin = 8; //RED
const byte StimPin[] = {7,6,5,4}; //Reward,AirPuff,TailShock,Conditioner

//---Initial state------------------
char state = 'C';

//---Timer variables----------------
SoftTimer nextStepTimer;
SoftTimer nextReadTimer;
     int  aT = 0;             //number of actualTrial
     byte trialCounter = 0;   //counter along one trial
unsigned long serDelay = 100; //delay between order and value reading

//---Parameters of the Trials-------
unsigned int  nT = 3;      //0:number of Trials

unsigned int  FR = 3200;   //1:ToneFrequency for Reward
unsigned int  FA = 800;    //2:ToneFrequency for AirPuff
unsigned int  FT = 200;    //3:ToneFrequency for TailShock
unsigned int  FC = 50;     //4:ToneFrequency for Conditioner

unsigned int  TL = 1000;   //5:ToneLength
unsigned int  GL = 1000;   //6:GapLength

unsigned int RwL = 250;    //7:RewardLength
unsigned int AiL = 250;    //8:AirPuffLength
unsigned int TaL = 250;    //9:TailShockLength
unsigned int CoL = 250;    //10:ConditionerLength

unsigned int  iT = 5;      //11:time interTrials (in s)
unsigned int dif = 1;      //12:diffusion factor for random iT component

unsigned int parVal[] = {nT,FR,FA,FT,FC,TL,GL,RwL,AiL,TaL,CoL,iT,dif};
unsigned int impulse = 1;  //binary code for stimuli
unsigned int stimuli[] = {nT,0,0,0}; //default stimulus: Reward
byte chosenStimulus = 0;

//---Union for bytes-integers-------
union ArrayToInt{
  byte array[2];
  unsigned int integer;
};

//---Communicational variables------
byte command = 0;
ArrayToInt value;
ArrayToInt toPyt;
bool ORDER = false;
