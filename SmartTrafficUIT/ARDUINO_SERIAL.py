import serial
import time
arduino = serial.Serial(port='COM10', baudrate=9600, timeout=0.1)

while True:
    # value = input("Enter a number: ") # Taking input from user
    arduino.write(bytes('1', 'utf-8'))
    time.sleep(0.05)
    # print(value)  # printing the value