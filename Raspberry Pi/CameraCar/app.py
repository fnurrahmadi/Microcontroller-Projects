from flask import Flask,render_template
import RPi.GPIO as GPIO
import subprocess
import time
import netifaces as ni
import signal
import sys

ni.ifaddresses('wlan0')
ip = ni.ifaddresses('wlan0')[ni.AF_INET][0]['addr']

app = Flask(__name__)

m1a = 27
m1b = 22
m2a = 23
m2b = 24

GPIO.setmode(GPIO.BCM) 
GPIO.setup(m1a, GPIO.OUT) 
GPIO.setup(m1b, GPIO.OUT)
GPIO.setup(m2a, GPIO.OUT)
GPIO.setup(m2b, GPIO.OUT)

subprocess.Popen(["/home/pi/CameraCar/mjpg", "start"])

def signal_handler(signal, frame):
	print('\nKeluar\n')
	GPIO.cleanup()
	sys.exit(0)
	
signal.signal(signal.SIGINT, signal_handler)

@app.route('/') 
def index():
	return render_template('index.html', ip=ip)

@app.route("/action/<state>")
def action(state):
    if state == 'maju':
        GPIO.output(m1a, GPIO.HIGH)
        GPIO.output(m1b, GPIO.LOW)
        GPIO.output(m2a, GPIO.HIGH)
        GPIO.output(m2b, GPIO.LOW)
        return 'Mobil Maju'
    elif state == 'mundur':
    	GPIO.output(m1a, GPIO.LOW)
	GPIO.output(m1b, GPIO.HIGH)
	GPIO.output(m2a, GPIO.LOW)
	GPIO.output(m2b, GPIO.HIGH)
	return 'Mobil Mundur'
    elif state == 'kanan':
	GPIO.output(m1a, GPIO.LOW)
        GPIO.output(m1b, GPIO.HIGH)
        GPIO.output(m2a, GPIO.HIGH)
        GPIO.output(m2b, GPIO.LOW)
        return 'Putar Kanan'
    elif state == 'kiri':
    	GPIO.output(m1a, GPIO.HIGH)
        GPIO.output(m1b, GPIO.LOW)
        GPIO.output(m2a, GPIO.LOW)
        GPIO.output(m2b, GPIO.HIGH)
        return 'Putar Kiri'
    elif state == 'off':
    	GPIO.output(m1a, GPIO.LOW)
        GPIO.output(m1b, GPIO.LOW)
        GPIO.output(m2a, GPIO.LOW)
        GPIO.output(m2b, GPIO.LOW)
        return 'mati'
    else:
    	return 'Salah'

try:
	if __name__ == '__main__':
	   app.run(debug=True, host='0.0.0.0')
except KeyboardInterrupt:  
    print "exit"
  
except:  
    print "Other error or exception occurred!"  
  
finally:  
    GPIO.cleanup() # this ensures a clean exit
    subprocess.Popen(["/home/pi/CameraCar/mjpg", "stop"])  
