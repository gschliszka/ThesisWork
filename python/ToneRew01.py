from tkinter import *
import time
import os
from ConnectWithArduino  import connect

version = "#Pyt_TonRew.0.20200416.1"
#version_ard = ""

parNam = ["Tone frequency(Hz):","Tone time(ms):","Gap time(ms):","Reward time(ms):",
          "Inter trial time(s):","Diffusion factor(s):","Number of trail:"]
initVal = [40,1000,1000,250,
            10,5,100]

class Serial_connector:
    ser = connect(115200)
    ser.write(version.encode())
    time.sleep(1)
    arduino_response = ser.readline().decode().split('\r\n')
    #print(arduino_response)
    arduino_program = arduino_response[0].split('#')
    #print(arduino_program)
    version_ard = arduino_program[1]
    print(version_ard)
    if version.split('.')[1]!=version_ard.split('.')[1]:
        print('GENERATIONS DIFFER! Potential incompatibility')

class Table:
    def __init__(self,master):
        self.parFrame = Frame(master,bg='black',bd=5,relief="ridge",width=200,height=200)
        self.parFrame.grid(column=0,row=0,sticky="NW")

        self.disFrame = Frame(master,bg='yellow',bd=5,relief="ridge",width=200,height=200)
        self.disFrame.grid(column=1,row=0)

class Diary:
    dirname = os.path.dirname(__file__)
    current_time = time.strftime('%Y_%m_%d_%H_%M_%S',time.localtime())
    dataFile = open(dirname+'/diary/'+current_time+'.txt','w')
    dataFile.write(version[1:]+'\n')
    def write_ard_version(self,vers_ard):
        self.dataFile.write(vers_ard+'\n\n')
    def title(self,title_value):
        self.dataFile.write(title_value+'\n\n')
    def close_diary(self):
        self.dataFile.close()
        time.sleep(3)

def update_parameters(event,i):
    if parVal[i].value!=parVal[i].spn.get() and parVal[i].spn.get().isnumeric():
        parVal[i].value=parVal[i].spn.get()
        print(parNam[i],parVal[i].spn.get())
        diary.dataFile.write(parNam[i]+parVal[i].spn.get()+'\n')
        parHist.lsb.insert(0,str(parNam[i])+' '+parVal[i].spn.get())
    else:
        parVal[i].spn['value'] = parVal[i].value
    if parHist.lsb.size()>3:
        parHist.lsb.delete(END)

class Parameters:
    def __init__(self,master,k):
        frame = Frame(master,bg='black',bd=0)
        frame.pack(fill=X)

        self.lbl = Label(frame,text=parNam[k],font=('Times New Roman Greek',10),anchor='w',width=20,bg='#9CB99C')
        self.lbl.grid(column=0,row=0)

        self.spn = Spinbox(frame,width=5,bd=2,from_=0,to=9999,justify='right')
        self.spn.bind("<FocusOut>",lambda event, a=k :update_parameters(event,a))
        self.spn.bind("<Return>",lambda event, a=k :update_parameters(event,a))
        self.spn.grid(column=1,row=0)
        self.spn['value'] = initVal[k]

        self.value = str(initVal[k])

class History:
    def __init__(self,master):
        lbf = LabelFrame(master,height=60,text="History:",font=('Times New Roman Greek',10),bg='#9CB99C')
        lbf.pack(fill=X,expand=YES)

        self.srb = Scrollbar(lbf,bg="blue",bd=2,width=14)
        self.srb.pack(side=RIGHT,fill=Y)

        self.lsb = Listbox(lbf,yscrollcommand=self.srb.set,bg='#9CB99C',width=30)
        self.lsb.insert(END,"Ready")
        self.lsb.pack(side=LEFT,fill=BOTH)
        
        self.srb.config(command=self.lsb.yview)

class Version_ID:
    def __init__(self,mester,id):
        self.lbl = Label(mester,text=id,font=('Times New Roman Greek',8),bg='#9CB99C')
        self.lbl.pack(fill=X)

connector = Serial_connector()

diary = Diary()
diary.write_ard_version(connector.version_ard)
diary.title('TONE REWARD TRIAL:')

window = Tk()
window.geometry('600x400+20+20')
window.minsize(200,200)

kernel = Table(window)

parVal =[]
for i in range(len(parNam)):
    parVal.append(Parameters(kernel.parFrame,i))

parHist = History(kernel.parFrame)
Version_ID(kernel.parFrame,version[1:])
Version_ID(kernel.disFrame,connector.version_ard)

window.mainloop()
diary.close_diary()