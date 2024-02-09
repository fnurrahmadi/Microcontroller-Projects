#import evdev
from evdev import InputDevice, categorize, ecodes
from time import sleep

#creates object 'gamepad' to store the data
#you can call it whatever you like
gamepad = InputDevice('/dev/input/event1')

#prints out device info at start
print(gamepad)

#evdev takes care of polling the controller in a loop
for event in gamepad.read_loop():
    #filters by event type
    if event.type == ecodes.EV_KEY:
        print(event)
	sleep(0.01)
