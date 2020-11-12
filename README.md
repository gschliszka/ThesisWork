
![Project Logo](/repository-open-graph.png)
# Tone&Stimulus Controlling System #
### for neurosciense behavior research ###
 
> App for thesis work, 2020.
>   Title: __*Control system for neuroscience behavior reasearch*__
>
>   by *Gáspár János Schliszka*
>    * [PPCU - Faculty of Information Technology and Bionics](https://itk.ppke.hu/en)
>    * In Vivo Neurophysiology Laboratory, [Institute of Experimental Medicine, HAS](http://koki.hu/english)

## Description ##
  Tone&Stimulus is a control system for a neuroscience behavior research. It consists of two pack of programs:
  - one for PC, to contol Arduino and create GUI
  - other one for Arduino UNO, to guide the experiment.
  
  The system made for controling a specific experiment which is a Pavlovian conditioning of two stimuli: a conditioned stimulus (CS, e.g. tone) and after that an unconditioned stmulus (UC, e.g. waterdrop, air puff). The experiment states out of trials: a pair of CS and UC stimulus.
  Trail has parameters, they are variable in run time:
  * number of trials (*nT*)
  * tone frequency (freq. for: Reward *FR*, Air Puff *FA*, Tail Shock *FT*, Empty *FE*)
  * tone length (*TL*)
  * gap length between tone and the stimulus (*GL*)
  * stimulus length (one by one: *RL*, *AL*, *TL*, *EL*)
  * duration between two trials: base (*iT*)
  * duration between two trials: random diffusion factor (*dif*)
  
  The program chooses from the selected stimuli randomly, however, every stimulus will be used the same times in an experiment or training session
  - [x] the numbers of stimuli are equal
  - [ ] nT by stimuli
  
  In the *History* part of the main window and a file in the *Diary* folder, users can easily check the changes along the session. In the *Display* module numbers of the left trials (by stimuli) are visible.
  - [ ] *Display* module
  
## Installing ##
  In the first place, the system requires one Arduino UNO board and one PC with an USB A-B cable.
  To programing the board and run the Python code you will need the [Arduino IDE](https://www.arduino.cc/en/software) and [Python 3.7](https://www.python.org/) to be installed on the PC with some additional libaries.
  See the necessary libraries below.
  
  ![Circuit for Arduino](/arduino/ToneStim.png)
  LEDs are modelling the real modules:
   * RED (pin 8): debug Tone
   * GREEN (pin 7): for Reward
   * RED (pin 6): for Air Puff
   * BLUE (pin 5): for Tail Shock
   * ORANGE (pin 4): for Empty (debug)
  
  #### Used libraries ####
   * Arduino: [SoftTimers.h](https://github.com/end2endzone/SoftTimers)
   * Python: [pyserial 3.4](https://pypi.org/project/pyserial/), [tkinter](https://docs.python.org/3/library/tkinter.html)
   - [ ] Arduino parameters and functions into library
   - [ ] add KEYWORDS.txt too
  
  Maybe there are some plus files in the repository whitch not required. They just halp in the development. The essential files are below.
  
  #### Essential files ####
   * Arduino: the whole [ToneStimTrial04](/arduino/ToneStimeTrial04) folder (open with IDE and upload to Arduino)
   * Python: [CommunicationProtocol.py](/python/CommunicationProtocol.py), [GlobalParameters.py](/pythonGlobalParameters.py), [GUI_.py](/python/GUI_.py), [ToneStim04.py](/python/ToneStim04.py) (in the same folder)
