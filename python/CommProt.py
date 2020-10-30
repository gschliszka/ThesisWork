from tkinter import *
import ConnectWithArduino as cwa
import _thread
import time

connector = cwa.Serial_connector()

def printing():
    while True:
        print('+3s')
        time.sleep(3)

root = Tk()
root.geometry('600x400+20+20')
root.title('Communication Protocol Test')

root.after(3000,_thread.start_new_thread,printing,())
root.mainloop()