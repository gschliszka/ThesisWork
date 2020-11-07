import tkinter as tk
import GlobalParameters as gp
import _thread

class Application:
    def __init__(self,master,connector,diary):
        self.parFrame = tk.Frame(master,bg='black',bd=5,relief="ridge",width=200,height=200)
        self.parFrame.grid(column=0,row=0,sticky="NW")

        self.parHist = self.History(self.parFrame)
        self.parVal =[]
        for i in range(len(gp.parNam)):
            self.parVal.append(self.Parameter(self.parFrame,connector,diary,self.parHist,i))
        self.Version_ID(self.parFrame,gp.version)

        self.disFrame = tk.Frame(master,bg='yellow',bd=5,relief="ridge",width=200,height=200)
        self.disFrame.grid(column=1,row=0,sticky="NW")

        self.Version_ID(self.disFrame,gp.ardVers)
        self.modifiers = self.Modifier(self.disFrame,connector,diary,self.parHist)
        self.buttons = self.Button(self.disFrame,connector,diary,self.parHist)
    
    class Parameter:
        def update_parameters(self,event,j):
            if self.value!=self.spn.get() and self.spn.get().isnumeric():
                self.value=self.spn.get()
                self.connector.writeOrder(j+10)
                self.connector.writeValue(self.value)
                print(gp.parNam[j],self.spn.get())
                self.diary.write_(gp.parNam[j]+self.spn.get()+'\n')
                self.parHist.lsb.insert(0,str(gp.parNam[j])+' '+self.spn.get())
            else:
                self.spn['value'] = self.value
            if self.parHist.lsb.size()>30:
                self.parHist.lsb.delete('end')

        def __init__(self,master,connector,diary,parHist,k):
            self.connector = connector
            self.diary = diary
            self.parHist = parHist
            
            self.frame = tk.Frame(master,bg='#9CB99C',bd=0)
            self.frame.pack(side='top',fill='x')

            self.lbl = tk.Label(master,text=gp.parNam[k],anchor='w',width=20,font=('Times New Roman Greek',10),bg='#9CB99C')
            self.lbl.grid(in_=self.frame,column=0,row=0)

            self.spn = tk.Spinbox(master,width=5,bd=2,justify='right')
            self.spn.bind("<FocusOut>",lambda event, a=k :self.update_parameters(event,a))
            self.spn.bind("<Return>",lambda event, a=k :self.update_parameters(event,a))
            self.spn.grid(in_=self.frame,column=1,row=0)
            self.spn['value'] = gp.initVal[k]

            self.value = str(gp.initVal[k])

    class History:
        def __init__(self,master):
            self.lbf = tk.LabelFrame(master,height=60,text="History:",font=('Times New Roman Greek',10),bg='#9CB99C')
            self.lbf.pack(side='bottom',fill='x',expand='yes')

            self.srb = tk.Scrollbar(master,bg="blue",bd=2,width=14)
            self.srb.pack(in_=self.lbf,side='right',fill='y')

            self.lsb = tk.Listbox(master,yscrollcommand=self.srb.set,bg='#9CB99C',width=30)
            self.lsb.insert('end',"Ready")
            self.lsb.pack(in_=self.lbf,side='left',fill='both')

            self.srb.config(command=self.lsb.yview)

    class Modifier:
        def data_recording(self):
            self.diary.write_('Rew: '+str(self.Svar[0].get())+', '+
                              'AiP: '+str(self.Svar[1].get())+', '+
                              'TaS: '+str(self.Svar[2].get())+', '+
                              'Con: '+str(self.Svar[3].get()))
            self.parHist.lsb.insert(0,'R: '+str(self.Svar[0].get())+', '+
                                      'A: '+str(self.Svar[1].get())+', '+
                                      'T: '+str(self.Svar[2].get())+', '+
                                      'C: '+str(self.Svar[3].get()))
        def stimulate(self):
            self.impl = self.Svar[0].get()+self.Svar[1].get()*2+self.Svar[2].get()*4+self.Svar[3].get()*8
            self.connector.writeOrder(1)
            self.connector.writeValue(int(self.impl))
            self.data_recording()
            print("pyt: Stimulus: " + str(self.impl))
            print(self.impl)
        def __init__(self,master,connector,diary,parHist):
            self.connector = connector
            self.diary = diary
            self.parHist = parHist
            self.impl = 0

            self.frame = tk.Frame(master,bg='#9CB99C',width=100,height=100)
            self.frame.pack(side='left',fill='y')

            self.Svar = [tk.IntVar(),tk.IntVar(),tk.IntVar(),tk.IntVar()]
            self.Svar[0].set(1)
            self.C1 = tk.Checkbutton(master,variable=self.Svar[0],bg='#9CB99C',command=self.stimulate,text="reward")
            self.C1.grid(in_=self.frame,column=0,row=0,sticky="NW")
            self.C2 = tk.Checkbutton(master,variable=self.Svar[1],bg='#9CB99C',command=self.stimulate,text="air puff")
            self.C2.grid(in_=self.frame,column=0,row=1,sticky="NW")
            self.C3 = tk.Checkbutton(master,variable=self.Svar[2],bg='#9CB99C',command=self.stimulate,text="tail shock")
            self.C3.grid(in_=self.frame,column=0,row=2,sticky="NW")
            self.C4 = tk.Checkbutton(master,variable=self.Svar[3],bg='#9CB99C',command=self.stimulate,text="conditioner")
            self.C4.grid(in_=self.frame,column=0,row=4,sticky="NW")

    class Button:
        def data_recording(self,k):
            if k==2:
                self.diary.write_('Trial started')
                self.parHist.lsb.insert(0,'Start')
            if k==3:
                self.diary.write_('Trial stopped')
                self.parHist.lsb.insert(0,'Stop')
            if k==4:
                self.diary.write_('Trial reset')
                self.parHist.lsb.insert(0,'Reset')
        def action(self,n):
            self.connector.writeOrder(n)
            self.connector.writeValue(0)
            self.data_recording(n)
        def __init__(self,master,connector,diary,parHist):
            self.connector = connector
            self.diary = diary
            self.parHist = parHist

            self.frame = tk.Frame(master,bg='blue',width=100,height=100)
            self.frame.pack(side='top')

            self.start = tk.Button(master,width=5,height=1,text="Start",command=lambda: self.action(2))
            self.start.pack(in_=self.frame,side='top')
            self.stop  = tk.Button(master,width=5,height=1,text="Stop",command=lambda: self.action(3))
            self.stop.pack(in_=self.frame,side='top')
            self.reset = tk.Button(master,width=5,height=1,text="Reset",command=lambda: self.action(4))
            self.reset.pack(in_=self.frame,side='top')
    
    #class Display:

    class Version_ID:
        def __init__(self,master,id):
            self.lbl = tk.Label(master,text=id,font=('Times New Roman Greek',8),bg='#9CB99C')
            self.lbl.pack(side='bottom',fill='x')

def tone_stimulus(connector,diary):
    root = tk.Tk()
    try:
        pic = tk.PhotoImage(file='icon01.png')
        root.iconphoto(False,pic)
    except:
        print(' >> Missing icon file!')
    root.geometry('370x500+20+60')
    root.minsize(370,500)
    root.title('Tone-Reward trials')

    diary.write_(gp.version)
    diary.write_(gp.ardVers)
    diary.write_("")
    Application(root,connector,diary)

    root.after(0,_thread.start_new_thread,connector.inComingData,())
    root.mainloop()