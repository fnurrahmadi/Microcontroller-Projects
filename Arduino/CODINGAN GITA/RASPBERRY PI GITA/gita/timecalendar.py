import time
##import calendar

try:
	while True:
		ticks = time.time()
		now = time.ctime(ticks)
		
		print("The Time Now is: ")
		print(ticks)
		print(now)

		time.sleep(1)
#except Exception:
 #   print("Exception Handled")

except KeyboardInterrupt:
    print("done")
