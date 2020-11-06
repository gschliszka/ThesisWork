import CommunicationProtocol as cp
import GUI_ as gui
import os

class Diary:
    def __init__(self):
        dirname = os.path.dirname(os.path.abspath(__file__))
        current_time = cp.time.strftime('%Y_%m_%d_%H_%M_%S',cp.time.localtime())
        try:
            self.dataFile = open(dirname+'/diary/'+current_time+'.txt','w')
        except OSError:
            print('Creat diary folder')
            os.mkdir(dirname+'/diary')
            self.dataFile = open(dirname+'/diary/'+current_time+'.txt','w')
    def write_(self,text):
        self.dataFile.write(text+'\n')
    def close_diary(self):
        self.dataFile.close()
        print('diary closed')
        cp.time.sleep(1)

connector = cp.Serial_connector()
diary = Diary()
gui.tone_stimulus(connector,diary)
diary.close_diary()