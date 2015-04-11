# Python arduino interface
import serial
ser = serial.Serial('/dev/tty.usbmodem1411', 9600)
# while True:
#     print ser.readline();


ser.write("1.45")
print "done"
