import time
import pyrebase
import string
import serial

config = {
	"apiKey": "AIzaSyCPBHJMghH2s2wJZPR5S5bkKo4FUv4pkro",
	"authDomain": "tugasakhirgita-dc01.firebaseapp.com",
	"databaseURL": "https://tugasakhirgita-dc01.firebaseio.com",
	"storageBucket": "tugasakhirgita-dc01.appspot.com"
}

firebase = pyrebase.initialize_app(config)

db = firebase.database()

#counter = 0
result = []

try:
	while True:
		with serial.Serial('/dev/ttyUSB0', 9600, timeout=1) as ser:
			received = ser.readline()
			time.sleep(5)
			result = received.decode("utf-8")
			result = result.replace("\r","")
			result = result.replace("\n","")
			result = result.split(",")
			print(result)
            
		local = time.localtime()
		year = local.tm_year
		month = local.tm_mon
		day = local.tm_mday
		hour = local.tm_hour
		minute = local.tm_min
		second = local.tm_sec

		db.child("P1").child(year).child(month).child(day).child(hour).child(minute).child(second).set(result[0])
		db.child("P2").child(year).child(month).child(day).child(hour).child(minute).child(second).set(result[1])
		db.child("P3").child(year).child(month).child(day).child(hour).child(minute).child(second).set(result[2])
		db.child("P4").child(year).child(month).child(day).child(hour).child(minute).child(second).set(result[3])
		db.child("P5").child(year).child(month).child(day).child(hour).child(minute).child(second).set(result[4])
		db.child("P6").child(year).child(month).child(day).child(hour).child(minute).child(second).set(result[5])
		db.child("P7").child(year).child(month).child(day).child(hour).child(minute).child(second).set(result[6])
		db.child("P8").child(year).child(month).child(day).child(hour).child(minute).child(second).set(result[7])
		db.child("P9").child(year).child(month).child(day).child(hour).child(minute).child(second).set(result[8])
		db.child("P10").child(year).child(month).child(day).child(hour).child(minute).child(second).set(result[9])
		
		result = 0

		#for x in range(len(result)):
		#	db.child("P"+str(x)).child(year).child(month).child(day).child(hour).child(minute).child(second).set(result[x])

		#counter = counter + 1

#except Exception:
#	print("Exception Handled")


except KeyboardInterrupt:
	print("done")