mjpg_streamer -i "input_raspicam.so -x 640 -y 360 -fps 15 -quality 50 -vf -hf" -o "output_http.so -p 8080 -w /usr/local/share/mjpg-streamer/www"
