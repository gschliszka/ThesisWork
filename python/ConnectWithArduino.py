import serial.tools.list_ports
import GlobalParameters as gp
import time

def get_ports():
    ports = serial.tools.list_ports.comports()
    return ports

def findArduino(portsFound):
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

def connect(rate):
    foundPorts = get_ports()        
    connectPort = findArduino(foundPorts)
    if connectPort != 'None':
        print('Connected to ' + connectPort)
        return serial.Serial(connectPort,baudrate=rate,timeout=1)
    else:
        print('Connection Issue!')
    print('DONE')

class Serial_connector():
    ser = connect(gp.baudrate)
    #ser.write(version.encode())
    time.sleep(1)
    arduino_response = ser.readline().decode().split('\r\n')
    #print(arduino_response)
    arduino_program = arduino_response[0].split('#')
    #print(arduino_program)
    version_ard = arduino_program[1]
    print(version_ard)
    if gp.version.split('.')[1]!=version_ard.split('.')[1]:
        print('GENERATIONS DIFFER! Potential incompatibility')

#serial_connect = connect(115200)