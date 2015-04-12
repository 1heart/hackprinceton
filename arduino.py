# Python arduino interface
import serial, time
ser = serial.Serial('/dev/tty.usbmodem1411', 9600)
# while True:
#     print ser.readline();

ser.write("0.57")



print "done"
