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

result = ["0","0","0","0","0","0","0","0","0","0"]
lastresult = ["0","0","0","0","0","0","0","0","0","0"]
counter = 0

try:
	countp1 = db.child("P1").child("countp1").get().val()
	countp2 = db.child("P2").child("countp2").get().val()
	countp3 = db.child("P3").child("countp3").get().val()
	countp4 = db.child("P4").child("countp4").get().val()
	countp5 = db.child("P5").child("countp5").get().val()
	countp6 = db.child("P6").child("countp6").get().val()
	countp7 = db.child("P7").child("countp7").get().val()
	countp8 = db.child("P8").child("countp8").get().val()
	
	while True:
		with serial.Serial('/dev/ttyUSB0', 2400, timeout=10) as ser:
			time.sleep(1)
			received = ser.readline()
			time.sleep(1)
			#print(received)
			result = received.decode("utf-8")
			result = result.replace("\r","")
			result = result.replace("\n","")
			result = result.split(",")
			#print(result)

		if result[0] != lastresult[0]:
			if result[0] == '0':
				print("Parkiran P1 Kosong")	
			elif result[0] == '1':
				print("Parkiran P1 Terisi")
				countp1 = countp1 + 1
				db.child("P1").child("isi").set(result[0])
				db.child("P1").child("countp1").set(countp1)
		if result[1] != lastresult[1]:
			if result[1] == '0':
				print("Parkiran P2 Kosong")	
			elif result[1] == '1':
				print("Parkiran P2 Terisi")
				countp2 = countp2 + 1
				db.child("P2").child("isi").set(result[1])
				db.child("P2").child("countp2").set(countp2)
		if result[2] != lastresult[2]:
			if result[2] == '0':
				print("Parkiran P3 Kosong")	
			elif result[2] == '1':
				print("Parkiran P3 Terisi")
				countp3 = countp3 + 1
				db.child("P3").child("isi").set(result[2])
				db.child("P3").child("countp3").set(countp3)
		if result[3] != lastresult[3]:
			if result[3] == '0':
				print("Parkiran P4 Kosong")	
			elif result[3] == '1':
				print("Parkiran P4 Terisi")
				countp4 = countp4 + 1
				db.child("P4").child("isi").set(result[3])
				db.child("P4").child("countp4").set(countp4)
		if result[4] != lastresult[4]:
			if result[4] == '0':
				print("Parkiran P5 Kosong")	
			elif result[4] == '1':
				print("Parkiran P5 Terisi")
				countp5 = countp5 + 1
				db.child("P5").child("isi").set(result[4])
				db.child("P5").child("countp5").set(countp5)
		if result[5] != lastresult[5]:
			if result[5] == '0':
				print("Parkiran P6 Kosong")	
			elif result[5] == '1':
				print("Parkiran P6 Terisi")
				countp6 = countp6 + 1
				db.child("P6").child("isi").set(result[5])
				db.child("P6").child("countp6").set(countp6)
		if result[6] != lastresult[6]:
			if result[6] == '0':
				print("Parkiran P7 Kosong")	
			elif result[6] == '1':
				print("Parkiran P7 Terisi")
				countp7 = countp7 + 1
				db.child("P7").child("isi").set(result[6])
				db.child("P7").child("countp7").set(countp7)
		if result[7] != lastresult[7]:
			if result[7] == '0':
				print("Parkiran P8 Kosong")	
			elif result[7] == '1':
				print("Parkiran P7 Terisi")
				countp8 = countp8 + 1
				db.child("P8").child("isi").set(result[7])
				db.child("P8").child("countp8").set(countp8)

		for j in range(8):
			lastresult[j] = result[j]
		
		counter = countp1 + countp2 + countp3 + countp4 + countp5 + countp6 + countp7 + countp8
		db.child("Counter").set(counter)
		
		result = []
		print("Waiting 10 seconds")
		time.sleep(10)

#except Exception:
#	print("Error occured; Exception Handled")

except KeyboardInterrupt:
	print("done")
