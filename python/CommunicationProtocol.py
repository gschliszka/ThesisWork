import serial.tools.list_ports
import GlobalParameters as gp
import time
import struct

class Serial_connector():
    # Open the port
    def __init__(self):
        self.ser = self.connect(gp.baudrate)
        time.sleep(1)
        arduino_response = self.ser.readline().decode().split('\r\n')
        #print(arduino_response)
        arduino_program = arduino_response[0].split('#')
        #print(arduino_program)
        self.version_ard = arduino_program[1]
        print(self.version_ard)
        if gp.version.split('.')[1]!=self.version_ard.split('.')[1]:
            print('GENERATIONS DIFFER! Incompatibility is probable')
    
    def connect(self,rate):
        foundPorts = serial.tools.list_ports.comports()        
        connectPort = self.findArduino(foundPorts)
        if connectPort != 'None':
            print('Connected to ' + connectPort)
            return serial.Serial(connectPort,baudrate=rate,timeout=1)
        else:
            print('Connection Issue!')
        print('DONE')
    def findArduino(self,portsFound):
        commPort = 'None'
        numConnection = len(portsFound)
        for i in range(0,numConnection):
            port = portsFound[i]
            strPort = str(port)
            print(strPort)
            if 'Arduino' in strPort: 
                splitPort = strPort.split(' ')
                commPort = (splitPort[0])
        return commPort

    # Communicational functions
    def readOrder(self):
        order = struct.unpack('<B',self.ser.read(1))[0]
        return order
    def writeOrder(self,n):
        self.ser.write(struct.pack('<B',int(n)))
        if self.readOrder()!=int(n):
            print('Incorrect order-transfer!')
    def readValue(self):
        return struct.unpack('<H',self.ser.read(2))[0]
    def writeValue(self,n):
        self.ser.write(struct.pack('<H',int(n)))
        if self.readValue()!=int(n):
            print('Incorrect value-transfer!')
    
    # Reader thread
    def inComingData(self):
        while True:
            if self.ser.inWaiting()>1:
                print(self.readOrder())
