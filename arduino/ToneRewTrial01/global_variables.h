/*
	global_variable.h - Library for TonRewTrial
	Created by Gaspar J. Schliszka
*/

//---Pin variables------------------
const int  TonePin = 8; //RED
const int    RwPin = 7; //GREEN
const int PiezoPin = 9; //buzzer

//---Initial state------------------
char state = 'D';

//---Timer variables----------------
unsigned long  zTime = 0;   //start time of training ~zeroTime (in ms)
unsigned long  aTime = 0;   //actualTime in doTrail()
int  randT = 0;   //iT+random(-dif,dif+1)
int     aT = 0;   //number of actualTrial

//---Additional timer variabels-----
bool  bTT = false;
bool   bg = false;
bool bRwT = false;
bool  biT = false;
bool newT = false;

//---Parameters of the Trials-------
int  TF = 100;    //ToneFrequency
int  TT = 1000;   //ToneTime
int   g = 1000;   //gap
int RwT = 250;    //RewardTime
int  iT = 5;      //time interTrials (in s)
int dif = 1;      //diffusion factor for random iT component
int  nT = 3;      //number of Trials
