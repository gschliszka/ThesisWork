import serial.tools.list_ports

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
    
#serial_connect = connect(115200)