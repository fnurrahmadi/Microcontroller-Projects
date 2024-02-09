from flask import Flask
from multiprocessing import Process
import pyrebase
##import serial
import time
from timeloop import Timeloop
from datetime import timedelta

import random

##Firebase Config
config = {
    "apiKey": "AIzaSyCPBHJMghH2s2wJZPR5S5bkKo4FUv4pkro",
    "authDomain": "tugasakhirgita-dc01.firebaseapp.com",
    "databaseURL": "https://tugasakhirgita-dc01.firebaseio.com",
    "storageBucket": "tugasakhirgita-dc01.appspot.com"
}

##Firebase Init
firebase = pyrebase.initialize_app(config)
db = firebase.database()

##Flask App Init
app = Flask(__name__)

##Timeloop Init
t1 = Timeloop()

##Variables
result = []

##Parsing Function on Timeloop
@t1.job(interval=timedelta(seconds=5))
def parsing():
    global result
    ##Serial Read from Arduino
    #with serial.Serial('/dev/ttyUSB0', 9600, timeout=1) as ser:
    #    received = ser.readline() #read until \n
    #    result = received.split(",") #split into list
    for y in range(8):
        result[y] = random.randint(0,1)
    
    ##Get Timestamp
    local = time.localtime()
    year = local.tm_year
    month = local.tm_mon
    day = local.tm_mday
    hour = local.tm_hour
    minute = local.tm_min
    second = local.tm_sec

    ##Loop 0-9
    for x in range(8):
        ##Upload to Firebase Database
        db.child("P"+str(x)).child(year).child(month).child(day).child(hour).child(minute).child(second).set(result[x])

    ##One Second Delay
    #time.sleep(1)

##Index Page
@app.route('/index')
def index():
    ##Multiprocessing Parsing Function
    global proc1
    proc1 = Process(target=parsing, args=(15))
    proc1.start()
    
    return render_template('index.html', result=result)

##Run App
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
    t1.start(block=True)
