from tkinter import *
import os

version = "#Pyt_TonRew.0.20200415.0"

parNam = ["Tone frequency(Hz):","Tone time(ms):","Reward time(ms):",
              "Gap time(ms):","Inter trial time(s):","Number of trail:"]

"""
class Table:
    def __init__(self,master):
        parFrame = Frame(master,bg='black',bd=5,relief="ridge",width=200,height=200)
        parFrame.grid(column=0,row=0)

        disFrame = Frame(master,bg='yellow',bd=5,relief="ridge",width=200,height=200)
        disFrame.grid(column=1,row=0)
"""

def writeHistory(event,i):
    print(parNam[i],parVal[i].spn.get())
    parHist.lsb.insert(0,str(parNam[i])+' '+parVal[i].spn.get())
    if parHist.lsb.size()>30:
        parHist.lsb.delete(END)

class Parameters:
    def __init__(self,master,k):
        frame = Frame(master,bg='black',bd=0)
        frame.pack(fill=X)

        self.lbl = Label(frame,text=parNam[k],font=('Times New Roman Greek',10),anchor='w',width=20,bg='#9CB99C')
        self.lbl.grid(column=0,row=0)

        self.spn = Spinbox(frame,width=5,bd=2,from_=0,to=9999,justify='right')
        self.spn.bind("<FocusOut>",lambda event, a=k :writeHistory(event,a))
        self.spn.bind("<Return>",lambda event, a=k :writeHistory(event,a))
        self.spn.grid(column=1,row=0)

class History:
    def __init__(self,master):
        lbf = LabelFrame(master,height=60,text="History:",font=('Times New Roman Greek',10),bg='#9CB99C')
        lbf.pack(fill=BOTH,expand=YES)

        self.srb = Scrollbar(lbf,bg="blue",bd=2,width=14)
        self.srb.pack(side=RIGHT,fill=Y)

        self.lsb = Listbox(lbf,yscrollcommand=self.srb.set,bg='#9CB99C',width=30)
        self.lsb.insert(END,"Ready")
        self.lsb.pack(side=LEFT,fill=BOTH)
        
        self.srb.config(command=self.lsb.yview)

dirname = os.path.dirname(__file__)
print(dirname)
window = Tk()
window.geometry('600x400+20+20')
window.minsize(200,200)

parFrame = Frame(window,bg='green',bd=5,relief="ridge",width=200,height=600)
parFrame.grid(column=0,row=0,sticky="NW")

parVal =[]

parVal.append(Parameters(parFrame,0))
parVal.append(Parameters(parFrame,1))
parVal.append(Parameters(parFrame,2))
parVal.append(Parameters(parFrame,3))
parVal.append(Parameters(parFrame,4))
parVal.append(Parameters(parFrame,5))

parHist = History(parFrame)

disFrame = Frame(window,bg='yellow',bd=5,relief="ridge",width=200,height=200)
disFrame.grid(column=1,row=0)

window.mainloop()