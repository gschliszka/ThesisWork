from tkinter import *
import CommunicationProtocol as cp
import _thread
import time

connector = cp.Serial_connector()

def printing():
    while True:
        print('+3s')
        time.sleep(3)

root = Tk()
root.geometry('600x400+20+20')
root.title('Communication Protocol Test')

root.after(0,_thread.start_new_thread,connector.inComingData,())
root.mainloop()