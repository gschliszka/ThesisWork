"""Serial:"""
version = "Pyt_TonStim.4.20201111.3"
ardVers = ""
baudrate = 115200

"""GUI colours:"""
background = 'black'
borders = 'yellow'
indicators = '#ff0000'
inputs = '#9c0303'
inlabelback = '#424242'
texts = '#00ff08'

"""Parameters:"""
nOrders = 10

nArdRes = 100

parNam = ["Number of rewards:",
          "Number of air puffs:",
          "Number of tail shocks:",
          "Number of emptys:",
          "TonFreq.(Hz) reward:",
          "TonFreq.(Hz) air puff:",
          "TonFreq.(Hz) tail shock:",
          "TonFreq.(Hz) empty:",
          "Tone length(ms):",
          "Gap length(ms):",
          "Length(ms): reward:",
          "Length(ms): air puff:",
          "Length(ms): tail shock:",
          "Length(ms): empty:",
          "Time inter trials(s):",
          "Diffusion factor(s):"]
          
initVal = [3,0,0,0,
           3200,800,200,50,
           1000,
           1000,
           250,250,250,250,
           5,
           1]