from flask import Flask, render_template
import subprocess
import pyrebase
import time

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

##Variables
#ep1, ep2, ep3, ep4, ep5, ep6, ep7, ep8 = 0
#up1, up2, up3, up4, up5, up6, up7, up8 = 0
now = 0
counter = 0

##Index Page
@app.route('/index')
def index():
	counter = db.child("Counter").get().val()
	p1 = db.child("P1").child("countp1").get().val()
	p2 = db.child("P2").child("countp2").get().val()
	p3 = db.child("P3").child("countp3").get().val()
	p4 = db.child("P4").child("countp4").get().val()
	p5 = db.child("P5").child("countp5").get().val()
	p6 = db.child("P6").child("countp6").get().val()
	p7 = db.child("P7").child("countp7").get().val()
	p8 = db.child("P8").child("countp8").get().val()
	
	#now = time.ctime(int(time.time()))
	
	return render_template('index.html', counter=counter, p1=p1, p2=p2, p3=p3, p4=p4, p5=p5, p6=p6, p7=p7, p8=p8)

##Run App
if __name__ == '__main__':
	##Subprocess Init
	app.run(host='0.0.0.0', port=5000, debug=True)
	subprocess.Popen(['python3','systemrun.py'])
