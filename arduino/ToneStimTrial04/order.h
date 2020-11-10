#define N_ORDERS 10
#define N_STIM 4

enum CODER{
  NOTHING = 0,
//Control:
  MODIFIER = 1,
  START    = 2,
  STOP     = 3,
  RESET    = 4,
//Arduino write:
  ACTUAL_N = 5,
  TRIAL_N  = 6,
  STIMULI  = 7,
  _______  = 8,
  END_TRS  = 9,
//Parameters:
  N_OF_TRS      = 10,
  TON_FREQ_Rew  = 11,
  TON_FREQ_AiP  = 12,
  TON_FREQ_TiS  = 13,
  TON_FREQ_Con  = 14,
  TONE_TIME     = 15,
  GAP           = 16,
  REWARD_L      = 17,
  AIR_PUFF_L    = 18,
  TAIL_SHOCK_L  = 19,
  CONDITIONER_L = 20,
  T_INTER_TRIAL = 21,
  DIFFUSION_F   = 22
};

enum STIMULUS{
  TONE_IMIT  = 0,
  REWARD     = 1,
  AIR_PUFF   = 2,
  TAIL_SHOCK = 3,
  EMPTY      = 4
};
