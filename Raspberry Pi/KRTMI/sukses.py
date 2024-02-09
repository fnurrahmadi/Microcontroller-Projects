#import evdev
from evdev import InputDevice, categorize, ecodes
import serial
from time import sleep

#creates object 'gamepad' to store the data
#you can call it whatever you like
gamepad = InputDevice('/dev/input/event1')
#initialize serial communication
ser = serial.Serial('/dev/ttyACM0', 9600)
sleep(5)
print "READY"

#button code variables (change to suit your device)
A = 193
B = 194
X = 134
Y = 138

up = 189
down = 190
left = 191
right = 192

start = 132
select = 130

RT = 133
RB = 136
LT = 137
LB = 135

#prints out device info at start
print(gamepad)

#loop and filter by event code and print the mapped label

for event in gamepad.read_loop():
    if event.type == ecodes.EV_KEY:
        if event.value == 1:
            if event.code == up:
                ser.write('1')
                print("Up")
                sleep(0.001)
            elif event.code == right:
                ser.write('2')
                print("Right")
                sleep(0.001)
            elif event.code == down:
                ser.write('3')
                print("Down")
                sleep(0.001)
            elif event.code == left:
                ser.write('4')
                print("Left")
                sleep(0.001)

            elif event.code == Y:
                ser.write('5')
                print("Y")
                sleep(0.001)
            elif event.code == B:
                ser.write('6')
                print("B")
                sleep(0.001)
            elif event.code == A:
                ser.write('7')
                print("A")
                sleep(0.001)
            elif event.code == X:
                ser.write('8')
                print("X")
                sleep(0.001)

            elif event.code == LT:
                ser.write('L')
                print("LT")
                sleep(0.001)
            elif event.code == RT:
                ser.write('R')
                print("RT")
                sleep(0.001)

            elif event.code == LB:
                ser.write('0')
                print("LB")
                sleep(0.001)
            elif event.code == RB:
                ser.write('9')
                print("RB")
                sleep(0.001)

            elif event.code == start:
                ser.write('A')
                print("start")
                sleep(0.001)
            elif event.code == select:
                ser.write('B')
                print("select")
                sleep(0.001)
