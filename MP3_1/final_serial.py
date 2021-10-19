import serial
import time

arduino = serial.Serial(port = '/dev/cu.usbmodem1101', baudrate=9600, timeout=0)
time.sleep(2)

while True:

    print ("Enter new speed or threshold value: ")

    var = str(input())
    print ("You Entered :", var)

    arduino.write(str.encode(var))
    time.sleep(1)