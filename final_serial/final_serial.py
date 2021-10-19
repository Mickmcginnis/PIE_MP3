import serial
import time

arduino = serial.Serial(port = '/dev/cu.usbmodem1101', baudrate=9600, timeout=0)
time.sleep(2)

print ("Enter new speed or threshold value. To change the motor speed, enter new speed as a whole number value followed by a 0 (e.g., to change the motor speed to 80, enter 800). To change the IR reflectance sensor threshold, enter the new threshold as a whole number value followed by a 1 (e.g., to change the threshold to 250, enter 2501)."
        )
while True:

    print("Enter new speed or threshold value:")

    var = str(input())
    print ("You Entered :", var)

    # write code to arduino port
    arduino.write(str.encode(var))
    time.sleep(1)