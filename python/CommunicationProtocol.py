import serial.tools.list_ports
import GlobalParameters as gp
import time
import struct

class Serial_connector():
    # Open the port
    def __init__(self):
        try:
            self.ser = self.connect(gp.baudrate)
            self.ser.reset_input_buffer()
            time.sleep(1)
            arduino_response = self.ser.readline().decode().split('\r\n')
        except:
            print("First connection failed")
            self.ser.close()
            self.ser = self.connect(gp.baudrate)
            self.ser.reset_input_buffer()
            time.sleep(1)
            arduino_response = self.ser.readline().decode().split('\r\n')
        #print(arduino_response)
        arduino_program = arduino_response[0].split('#')
        #print(arduino_program)
        gp.ardVers = arduino_program[1]
        print(gp.ardVers)
        if gp.version.split('.')[1]!=gp.ardVers.split('.')[1]:
            print(' >> GENERATIONS DIFFER! Incompatibility is probable')
        self.order = []
        self.value = []
    
    def connect(self,rate):
        foundPorts = serial.tools.list_ports.comports()        
        connectPort = self.findArduino(foundPorts)
        if connectPort != 'None':
            print('Connected to ' + connectPort)
            return serial.Serial(connectPort,baudrate=rate,timeout=1)
        else:
            print('Connection Issue!')
            time.sleep(2)
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
        #if self.readOrder()!=int(n):
        #    print('Incorrect order-transfer!')
    def readValue(self):
        return struct.unpack('<H',self.ser.read(2))[0]
    def writeValue(self,n):
        self.ser.write(struct.pack('<H',int(n)))
        #if self.readValue()!=int(n):
        #    print('Incorrect value-transfer!')
    
    # Reader thread
    def inComingData(self):
        while True:
            if self.ser.inWaiting()>2:
                order = self.readOrder()
                value = self.readValue()
                if(order==8):
                    #self.order = self.readOrder() ### self.order.append(self.readOrder())
                    #self.value = self.readValue()
                    self.order.append(self.readOrder())
                    self.value.append(self.readValue())
                    print('Arduino: '+str(self.order)+": "+str(self.value))
                else:
                    print(str(order) + ': ' + str(value))
                time.sleep(0.1)