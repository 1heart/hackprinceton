# Python arduino interface
import serial, time
try:
	ser = serial.Serial('/dev/tty.usbmodem621', 9600)
except:
	print "Arduino appears not to be attached."
# while True:
#     print ser.readline();

# ser.write("0.59")



# print "done"

def send_to_arduino(number):
	string_number = str(number)[0:3]
	if string_number == "0.0":
		string_number = "0.1"
	print "I'm sending to arduino ", string_number
	ser.write(string_number)

def clear():
	ser.write("9.0")
