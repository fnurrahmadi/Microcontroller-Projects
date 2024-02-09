from flask import Flask, render_template
import pyrebase

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
p1 = ""
p2 = ""
p3 = ""
p4 = ""
p5 = ""
p6 = ""
p7 = ""
p8 = ""
counter = 0

##Index Page
@app.route('/index')
def index():
        counter = db.child("Counter").get().val()
        ep1 = db.child("P1").child("isi").get().val()
        ep2 = db.child("P2").child("isi").get().val()
        ep3 = db.child("P3").child("isi").get().val()
        ep4 = db.child("P4").child("isi").get().val()
        ep5 = db.child("P5").child("isi").get().val()
        ep6 = db.child("P6").child("isi").get().val()
        ep7 = db.child("P7").child("isi").get().val()
        ep8 = db.child("P8").child("isi").get().val()

        if ep1 == '1':
                p1 = "Terisi"
        else:
                p1 = "Kosong"

        if ep2 == '1':
                p2 = "Terisi"
        else:
                p2 = "Kosong"

        if ep3 == '1':
                p3 = "Terisi"
        else:
                p3 = "Kosong"

        if ep4 == '1':
                p4 = "Terisi"
        else:
                p4 = "Kosong"

        if ep4 == '1':
                p4 = "Terisi"
        else:
                p4 = "Kosong"

        if ep5 == '1':
                p5 = "Terisi"
        else:
                p5 = "Kosong"

        if ep6 == '1':
                p6 = "Terisi"
        else:
                p6 = "Kosong"

        if ep7 == '1':
                p7 = "Terisi"
        else:
                p7 = "Kosong"

        if ep8 == '1':
                p8 = "Terisi"
        else:
                p8 = "Kosong"

        return render_template('mainpage-1.html', counter=counter, p1=p1, p2=p2, p3=p3, p4=p4, p5=p5, p6=p6, p7=p7, p8=p8)

##Run App
if __name__ == '__main__':
        app.run(host='0.0.0.0', port=5000, debug=True)
