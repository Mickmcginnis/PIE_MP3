import serial
import time

arduino = serial.Serial(port = '/dev/cu.usbmodem1101', baudrate=9600, timeout=0)
time.sleep(2)

while True:

    print ("Enter new speed or threshold value: ")

    var = str(input())
    print ("You Entered :", var)

    arduino.write(str.encode(var))
    # print("New threshold: {}".format(var))
    time.sleep(1)

    # if(var[0:2] == 's: '):
    #     arduino.write(str.encode('{}'.format(var)))
    #     print("Change motorspeed to {}".format(var[3::]))
    #     time.sleep(1)

    # if(var[0:2] == 't: '):
    #     arduino.write(str.encode('{}'.format(var)))
    #     print("Change threshold to {}".format(var[3::]))
    #     time.sleep(1)

    # if(var == '3'):
    #     arduino.write(str.encode('3'))
    #     print("LED turned on")
    #     time.sleep(1)

    # if(var == '4'):
    #     arduino.write(str.encode('4'))
    #     print("LED turned off")