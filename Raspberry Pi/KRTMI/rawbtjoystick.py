#import evdev
from evdev import InputDevice, categorize, ecodes
from time import sleep

#creates object 'gamepad' to store the data
#you can call it whatever you like
gamepad = InputDevice('/dev/input/event0')

#prints out device info at start
print(gamepad)

#evdev takes care of polling the controller in a loop
for event in gamepad.read_loop():
    print(categorize(event))
    sleep(0.01)
