import tkinter as tk
from tkinter import ttk
import CommunicationProtocol as cp
import _thread

class Display:
    def changed(self,k):
        #self.num.config(text=str(self.k)+'/'+str(self.l))
        self.contener[k].max = 100
        self.contener[k].pBar.config(maximum=self.contener[k].max)
        self.contener[k].var.set(80)
        self.contener[k].strNUM.set(self.contener[k].var.get())
        self.contener[k].strMAX.set('/ '+str(self.contener[k].max))
        #self.contener[k].str.set(str( self.contener[k].var.get())+"/"+str(self.contener[k].max))
        self.fin.config(text="Finished",bg='yellow')
    def __init__(self,master):
        self.frame = tk.LabelFrame(master,text="Display:",font=('Times New Roman Greek',10),bg='#9CB99C',width=100,height=100)
        self.frame.pack(side='top',fill='y')

        self.total = self.Progressbar(self.frame,'Total:',300)
        self.reward = self.Progressbar(self.frame,'Reward:',100,False)
        self.airpuff = self.Progressbar(self.frame,'Air puff:',100,False)
        self.tailShock = self.Progressbar(self.frame,'Reward:',100,False)
        self.empty = self.Progressbar(self.frame,'Empty:',100,False)
        self.contener = [self.total,self.reward,self.airpuff,self.tailShock,self.empty]

        self.butn = tk.Button(master,text="Update",command=lambda: self.changed(2))
        self.butn.pack(in_=self.frame)

        self.time = tk.Label(master,text="Time-out: 0s",font=('Times New Roman Greek',10),bg='#9CB99C')
        self.time.pack(in_=self.frame,side='left')

        self.fin = tk.Label(master,text="",font=('Times New Roman Greek',10),bg='#9CB99C')
        self.fin.pack(in_=self.frame,side='right')
 
    class Progressbar():
        def __init__(self,master,NAME,LENGTH,MAIN=True):
            self.max = 5
            self.var = tk.IntVar()
            self.var.set(2)

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
                self.lbl = tk.Label(master,text=NAME,width=15,anchor='e',font=('Times New Roman Greek',10),bg='#9CB99C')
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

root = tk.Tk()
d = Display(root)
#d.changed(2)
#d.contener[0].
#root.after(5000,_thread.start_new_thread,d.changed(3),())
root.mainloop()