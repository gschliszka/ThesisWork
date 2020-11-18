/*
	global_variable.h - Library for TonStimTrial
	Created by Gaspar J. Schliszka
*/
#include <SoftTimers.h>

//---Pin variables------------------
const byte  PiezoPin = 9;           //buzzer
const byte StimPin[] = {8,7,6,5,4}; //ToneImitation,Reward,AirPuff,TailShock,Conditioner
const byte  analogIn = A5;          //analog input
const byte digitalIn = 12;          //digital input

//---Initial state------------------
char state = 'C';
bool debug = false;

//---Timer variables----------------
SoftTimer nextStepTimer;      //timer between parts of the trial
SoftTimer nextReadTimer;      //timer between order and value reading
unsigned int aS[] = {0,0,0,0};//numbers of already used stimuli
     byte trialCounter = 0;   //counter along one trial
unsigned long serDelay = 0;   //delay between order and value reading

//---Parameters of the Trials-------
unsigned int  nR = 3;      //0:number of Rewards
unsigned int  nA = 0;      //1:number of AirPuffs
unsigned int  nT = 0;      //2:number of TailShocks
unsigned int  nE = 0;      //3:number of Emptys

unsigned int  FR = 3200;   //4:ToneFrequency for Reward
unsigned int  FA = 800;    //5:ToneFrequency for AirPuff
unsigned int  FT = 200;    //6:ToneFrequency for TailShock
unsigned int  FE = 50;     //7:ToneFrequency for Empty

unsigned int  TL = 1000;   //8:ToneLength
unsigned int  GL = 1000;   //9:GapLength

unsigned int RwL = 250;    //10:RewardLength
unsigned int AiL = 250;    //11:AirPuffLength
unsigned int TaL = 250;    //12:TailShockLength
unsigned int EmL = 250;    //13:EmptyLength

unsigned int  iT = 5;      //14:time interTrials (in s)
unsigned int dif = 1;      //15:diffusion factor for random iT component

unsigned int parVal[]  = {nR,nA,nT,nE,FR,FA,FT,FE,TL,GL,RwL,AiL,TaL,EmL,iT,dif};//values of the parameters
unsigned int impulse   = 1;               //binary code for stimuli
unsigned int stimuli[] = {0,nR,nA,nT,nE}; //default stimulus: Reward
byte chosenStimulus    = 0;               //number of the actual stimulus (from 0 to 4)

//---Union for bytes-integers-------
union ArrayToInt{       //halp to convert array to unsigned int
  byte array[2];
  unsigned int integer;
};

//---Communicational variables------
byte command = 0;   //container for order
bool ORDER = false; //halp in order-value reading
ArrayToInt value;   //container for value (from PC)
ArrayToInt toPyt;   //container for value (from Arduino)
