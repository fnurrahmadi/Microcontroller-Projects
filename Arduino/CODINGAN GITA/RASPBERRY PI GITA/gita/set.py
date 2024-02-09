import time
import pyrebase

config = {
    "apiKey": "AIzaSyCPBHJMghH2s2wJZPR5S5bkKo4FUv4pkro",
    "authDomain": "tugasakhirgita-dc01.firebaseapp.com",
    "databaseURL": "https://tugasakhirgita-dc01.firebaseio.com",
    "storageBucket": "tugasakhirgita-dc01.appspot.com"
}

firebase = pyrebase.initialize_app(config)

db = firebase.database()
counter = 0

try:
    while True:
        local = time.localtime()
        year = local.tm_year
        month = local.tm_mon
        day = local.tm_mday
        hour = local.tm_hour
        minute = local.tm_min
        second = local.tm_sec

        db.child(year).child(month).child(day).child(hour).child(minute).child(second).set(counter)
        counter = counter + 1

        time.sleep(1)

#except Exception:
#    print("Exception Handled")


except KeyboardInterrupt:
    print("done")
