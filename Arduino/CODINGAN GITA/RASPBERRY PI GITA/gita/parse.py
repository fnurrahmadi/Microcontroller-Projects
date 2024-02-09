import time
import string
import serial

while True:
	with serial.Serial('/dev/ttyUSB0', 9600, timeout=1) as ser:
		received = ser.readline() #read until \n
		#received = str(received)
		print(received)
		#result = received.split(",")
		#p1 = result[0]
		#p2 = result[1]
		#p3 = result[2]
		#p4 = result[3]
		#p5 = result[4]
		#p6 = result[5]
		#p7 = result[6]
		#p8 = result[7]
		#p9 = result[8]
		#p10 = result[9]
    

