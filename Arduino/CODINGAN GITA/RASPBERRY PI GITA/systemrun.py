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

result = ["0","0","0","0","0","0","0","0","0","0","0"]
lastresult = ["0","0","0","0","0","0","0","0","0","0","0"]
counter = 0
received = False

counter = db.child("Counter").get().val()

while True:
	try:
		with serial.Serial('/dev/ttyUSB0', 2400, timeout=10) as ser:
			time.sleep(1)
			received = ser.readline()
			time.sleep(1)
			print(received)
			#if len(received) != 0:
			result = received.decode("utf-8")
			result = result.replace("\r","")
			result = result.replace("\n","")
			result = result.split(",")
			print(result)
			#else:
			#	result = lastresult
				
			received = False

		if result[0] != lastresult[0]:
			if result[0] == '0':
				print("Parkiran P1 Kosong")
			elif result[0] == '1':
				counter = counter + 1
				print("Parkiran P1 Terisi")
			db.child("P1").child("isi").set(result[0])
		if result[1] != lastresult[1]:
			if result[1] == '0':
				print("Parkiran P2 Kosong")	
			elif result[1] == '1':
				print("Parkiran P2 Terisi")
				counter = counter + 1
			db.child("P2").child("isi").set(result[1])
		if result[2] != lastresult[2]:
			if result[2] == '0':
				print("Parkiran P3 Kosong")	
			elif result[2] == '1':
				print("Parkiran P3 Terisi")
				counter = counter + 1
			db.child("P3").child("isi").set(result[2])
		if result[3] != lastresult[3]:
			if result[3] == '0':
				print("Parkiran P4 Kosong")	
			elif result[3] == '1':
				print("Parkiran P4 Terisi")
				counter = counter + 1
			db.child("P4").child("isi").set(result[3])
		if result[4] != lastresult[4]:
			if result[4] == '0':
				print("Parkiran P5 Kosong")	
			elif result[4] == '1':
				print("Parkiran P5 Terisi")
				counter = counter + 1
			db.child("P5").child("isi").set(result[4])
		if result[5] != lastresult[5]:
			if result[5] == '0':
				print("Parkiran P6 Kosong")	
			elif result[5] == '1':
				print("Parkiran P6 Terisi")
				counter = counter + 1
			db.child("P6").child("isi").set(result[5])
		if result[6] != lastresult[6]:
			if result[6] == '0':
				print("Parkiran P7 Kosong")	
			elif result[6] == '1':
				print("Parkiran P7 Terisi")
				counter = counter + 1
			db.child("P7").child("isi").set(result[6])
		if result[7] != lastresult[7]:
			if result[7] == '0':
				print("Parkiran P8 Kosong")	
			elif result[7] == '1':
				print("Parkiran P8 Terisi")
				counter = counter + 1
			db.child("P8").child("isi").set(result[7])

		print(counter)
		db.child("Counter").set(counter)

		#for j in range(8):
		lastresult = result
		print(lastresult)

		#result = []
		print("Waiting (1 sec) ...")
		time.sleep(5)

	#except Exception:
	#	print("Error occured; Exception Handled. Continuing...")
	#	continue
	
	except KeyboardInterrupt:
		print("done")
		break
