#import evdev
from evdev import InputDevice, categorize, ecodes
import serial
from time import sleep

#creates object 'gamepad' to store the data
#you can call it whatever you like
gamepad = InputDevice('/dev/input/event1')
#initialize serial communication
ser = serial.Serial('/dev/ttyACM0', 9600)
sleep(3)
print "READY"

#button code variables (change to suit your device)
x = 304
o = 305
square = 308
triangle = 307

up = 544
down = 545
left = 546
right = 547

start = 315
select = 314

R1 = 311
R2 = 313
L1 = 310
L2 = 312

#prints out device info at start
print(gamepad)

#loop and filter by event code and print the mapped label

for event in gamepad.read_loop():
	if event.type == ecodes.EV_KEY:
##=====================================DIRECTIONAL PAD===========================================
		if event.value == 1:
			if event.code == up:
				ser.write('1')
				print("Up")
				sleep(0.001)
			if event.code == right:
				ser.write('2')
				print("Right")
				sleep(0.001)
			if event.code == down:
				ser.write('3')
				print("Down")
				sleep(0.001)
			if event.code == left:
				ser.write('4')
				print("Left")
				sleep(0.001)
				
		elif event.value == 0:
			if event.code == up:
				ser.write('0')
				print("Stop")
				sleep(0.001)
			if event.code == right:
				ser.write('0')
				print("Stop")
				sleep(0.001)
			if event.code == down:
				ser.write('0')
				print("Stop")
				sleep(0.001)
			if event.code == left:
				ser.write('0')
				print("Stop")
				sleep(0.001)

##=======================================SHARP MOVEMENT===========================================


##=======================================ACTION BUTTONS===========================================
		if event.value == 1:
			if event.code == x:
				ser.write('A')
				print("X")
				sleep(0.001)
			if event.code == o:
				ser.write('B')
				print("O")
				sleep(0.001)
			if event.code == square:
				ser.write('C')
				print("Square")
				sleep(0.001)
			if event.code == triangle:
				ser.write('D')
				print("Triangle")
				sleep(0.001)

##=========================================MENU BUTTONS===========================================
		if event.value == 1:
			if event.code == start:
				ser.write('V')
				print("Start")
				sleep(0.001)
			if event.code == select:
				ser.write('U')
				print("Select")
				sleep(0.001)

##=====================================SHOULDER BUTTONS==========================================
		if event.value == 1:
			if event.code == R1:
				ser.write('R')
				print("R1")
				sleep(0.001)
			if event.code == R2:
				ser.write('r')
				print("R2")
				sleep(0.001)
			if event.code == L1:
				ser.write('L')
				print("L1")
				sleep(0.001)
			if event.code == L2:
				ser.write('l')
				print("L2")
				sleep(0.001)
				
##=======================================ANALOG BUTTONS===========================================
		if event.value == 1:
			if event.code == R3:
				ser.write('')
				print("R3")
				sleep(0.001)
			if event.code == L3:
				ser.write('r')
				print("L3")
				sleep(0.001)
