import GUI_ as gui
import CommunicationProtocol as cp
import ToneStim04 as ts

root = gui.tk.Tk()
gui.Application(root,cp.Serial_connector())#,ts.Diary())
root.mainloop