#define N_ORDERS 10
#define N_STIM 4

enum PYT_DECODER{
  NOTHING = 0,
//Control:
  MODIFIER = 1,
  START    = 2,
  STOP     = 3,
  RESET    = 4,
//Arduino write:
  _______0  = 5,
  _______1   = 6,
  _______2   = 7,
  ARD_SEND  = 8,
  END_TRS   = 9,
  
//Parameters:
  N_OF_Rews     = 10,
  N_OR_AiPs     = 11,
  N_OF_TaS      = 12,
  N_OF_Emps     = 13,
  
  TON_FREQ_Rew  = 14,
  TON_FREQ_AiP  = 15,
  TON_FREQ_TaS  = 16,
  TON_FREQ_Emp  = 17,
  
  TONE_TIME     = 18,
  GAP           = 19,
  
  REWARD_L      = 20,
  AIR_PUFF_L    = 21,
  TAIL_SHOCK_L  = 22,
  CONDITIONER_L = 23,
  
  T_INTER_TRIAL = 24,
  DIFFUSION_F   = 25
};

enum STIMULUS{
  TONE_IMIT  = 0,
  REWARD     = 1,
  AIR_PUFF   = 2,
  TAIL_SHOCK = 3,
  EMPTY      = 4
};

enum ARD_CODER{
//Actual N of Stimulus:
  A_N_Rews = 100,
  A_N_AiPs = 101,
  A_N_TaSs = 102,
  A_N_Emps = 103,
//N of Stimulus in Stimuli[]
  S_N_Rews = 110,
  S_N_AiPs = 111,
  S_N_TaSs = 112,
  S_N_Empy = 113
};
