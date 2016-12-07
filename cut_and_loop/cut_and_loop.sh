sam=../resources/simpleGuitarRecording.wav
function installSubtools() {
	sudo apt-get install mpg321
	sudo curl -L https://yt-dl.org/downloads/latest/youtube-dl -o /usr/local/bin/youtube-dl
	sudo chmod a+rx /usr/local/bin/youtube-dl
}
function downloadFromYT() {
	youtube-dl $1 -o yt.webm
	ffmpeg -i yt.webm* -vn -ab 128k -ar 44100 -y yt.mp3
	mpg123 -w yt.wav yt.mp3	
}
function cut_audio() {
	sox "$1" "$2" trim "$3" "$4"
}
function fadeInOut() {
	sox "$1" tmp.wav fade l 0.3 $(soxi -d $1) 0.3 
	cp tmp.wav "$1"
	rm tmp.wav
}
function checkLength() {
	soxi -D "$1"
}
function loop() {
	while [[ 1 ]]; do
		play "$1"
		sleep $2
	done
}
function trainPart(){
	cut_audio "$1" part.wav "$2" "$3"
	fadeInOut part.wav
	loop part.wav $4
}
function ,ttr { trainPart yt.wav $1 $2 $3; }
trainPart yt.wav 0 3 
