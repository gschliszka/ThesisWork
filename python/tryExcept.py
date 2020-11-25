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