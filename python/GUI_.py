import tkinter as tk
from tkinter import ttk
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
        self.display = self.Display(self.disFrame,connector)
    
    class Parameter:
        def update_parameters(self,event,j):
            if self.value!=self.spn.get() and self.spn.get().isnumeric():
                self.value=self.spn.get()
                self.connector.writeOrder(j+gp.nOrders)
                self.connector.writeValue(self.value)
                print(gp.parNam[j],self.spn.get())
                self.diary.write_(gp.parNam[j]+self.spn.get())
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
            print("Pyton: modifier " + str(self.impl))
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
            self.C4 = tk.Checkbutton(master,variable=self.Svar[3],bg='#9CB99C',command=self.stimulate,text="empty")
            self.C4.grid(in_=self.frame,column=0,row=4,sticky="NW")

    class Button:
        def data_recording(self,k):
            if k==2:
                self.diary.write_('\nTrial started')
                self.parHist.lsb.insert(0,'Start')
            if k==3:
                self.diary.write_('\nTrial stopped')
                self.parHist.lsb.insert(0,'Stop')
            if k==4:
                self.diary.write_('\nTrial reset')
                self.parHist.lsb.insert(0,'Reset')
        def action(self,n):
            self.connector.writeOrder(n)
            self.connector.writeValue(0)
            self.data_recording(n)
        def __init__(self,master,connector,diary,parHist):
            self.connector = connector
            self.diary = diary
            self.parHist = parHist

            self.frame = tk.Frame(master,bg='#9CB99C',width=100,height=100)
            self.frame.pack(side='top',fill='both',expand=1)

            self.reset = tk.Button(master,width=5,height=1,text="Reset",command=lambda: self.action(4))
            self.reset.pack(in_=self.frame,side='right')

            self.stop  = tk.Button(master,width=5,height=1,text="Stop",command=lambda: self.action(3))
            self.stop.pack(in_=self.frame,side='right')

            self.start = tk.Button(master,width=5,height=1,text="Start",command=lambda: self.action(2))
            self.start.pack(in_=self.frame,side='right')
    
    class Display:
        def changed(self):
            while True:
                if len(self.connector.order)>0 and len(self.connector.value)>0:
                    order = self.connector.order.pop(0)
                    value = self.connector.value.pop(0)

                    """#Max number of one Stimulus"""
                    if order in range(10,14):
                        #print("Bent vagyok!")
                        self.contener[order-gp.nOrders+1].max = 0
                        self.contener[order-gp.nOrders+1].max = int(value)
                        self.contener[order-gp.nOrders+1].pBar.config(maximum=self.contener[order-gp.nOrders+1].max)
                        self.contener[0].max = 0
                        for i in range(1,len(self.contener)):
                            self.contener[0].max = self.contener[0].max+self.contener[i].max
                        self.contener[0].pBar.config(maximum=self.contener[0].max)
                        self.contener[order-gp.nOrders+1].strMAX.set('/ '+str(self.contener[order-gp.nOrders+1].max))
                        self.contener[0].strMAX.set('/ '+str(self.contener[0].max))
                        print("P.Readed: "+str(self.contener[order-gp.nOrders+1].var.get())+"/"+str(self.contener[order-gp.nOrders+1].max))

                    """#Number of already did Stimulus"""
                    if order in range(100,104):
                        self.contener[order-gp.nArdRes+1].var.set(int(value))
                        self.contener[0].var.set(0)
                        summation = 0
                        for i in range(1,len(self.contener)):
                            summation = self.contener[i].var.get()+summation
                        self.contener[0].var.set(summation)
                        self.contener[order-gp.nArdRes+1].strNUM.set(str(self.contener[order-gp.nArdRes+1].var.get()))
                        self.contener[0].strNUM.set(str(self.contener[0].var.get()))
                    
                    if order==24:
                        self.time.config(text="Time-out: "+str(int(value/1000))+'s')
                        self.fin.config(text="",bg='#9CB99C')
                    
                    if order==9:
                        self.fin.config(text="Finished",bg='yellow')
                        self.time.config(text="Time-out: ---")

                    order = 0
                    value = 0

        def __init__(self,master,connector):
            self.connector = connector
            self.frame = tk.LabelFrame(master,text="Display:",font=('Times New Roman Greek',10),bg='#9CB99C',width=100,height=100)
            self.frame.pack(side='bottom',fill='y')

            self.total = self.Progressbar(self.frame,'Total:',300)
            self.reward = self.Progressbar(self.frame,'Reward:',100,False)
            self.airpuff = self.Progressbar(self.frame,'Air puff:',100,False)
            self.tailShock = self.Progressbar(self.frame,'Reward:',100,False)
            self.empty = self.Progressbar(self.frame,'Empty:',100,False)
            self.contener = [self.total,self.reward,self.airpuff,self.tailShock,self.empty]

            self.time = tk.Label(master,text="Time-out: ---",font=('Times New Roman Greek',10),bg='#9CB99C')
            self.time.pack(in_=self.frame,side='left')

            self.fin = tk.Label(master,text="",font=('Times New Roman Greek',10),bg='#9CB99C')
            self.fin.pack(in_=self.frame,side='right')
    
        class Progressbar():
            def __init__(self,master,NAME,LENGTH,MAIN=True):
                self.max = 0
                self.var = tk.IntVar()
                self.var.set(0)

                self.strNUM = tk.StringVar()
                self.strNUM.set(str(self.var.get()))
                self.strMAX = tk.StringVar()
                self.strMAX.set('/ '+str(self.max))

                self.frame = tk.Frame(master,bg='#9CB99C')
                self.frame.pack(side='top',fill='x')

                self.core = tk.Frame(master,bg='#9CB99C')
                if MAIN:
                    self.lbl = tk.Label(master,text=NAME,font=('Times New Roman Greek',10),bg='#9CB99C')
                else:
                    self.lbl = tk.Label(master,text=NAME,font=('Times New Roman Greek',10),bg='#9CB99C',width=15,anchor='e')
                self.lbl.pack(in_=self.core,side='left')

                self.lNUM = tk.Label(master,font=('Times New Roman Greek',10),bg='#9CB99C',textvariable=self.strMAX)
                self.lNUM.pack(in_=self.core,side='right')
                self.lMAX = tk.Label(master,font=('Times New Roman Greek',10),bg='#9CB99C',textvariable=self.strNUM)
                self.lMAX.pack(in_=self.core,side='right')

                self.pBar = ttk.Progressbar(master,orient='horizontal',length=LENGTH,mode='determinate',variable=self.var,maximum=self.max)
                if MAIN:
                    self.core.pack(in_=self.frame,side='top',fill='x',padx=5)
                    self.pBar.pack(in_=self.frame,side='bottom',padx=5)
                else:
                    self.core.pack(in_=self.frame,side='left',padx=5)
                    self.pBar.pack(in_=self.core,side='left',padx=5)

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
    root.geometry('670x565+200+60')
    root.minsize(370,565)
    root.title('Tone-Reward trials')

    diary.write_(gp.version)
    diary.write_(gp.ardVers)
    diary.write_("")
    app = Application(root,connector,diary)

    root.after(0,_thread.start_new_thread,connector.inComingData,())
    root.after(1000,_thread.start_new_thread,app.display.changed,())

    root.mainloop()