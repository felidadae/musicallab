#!/bin/bash

#	source __run__.sh start mysynth
#
#

BUFFER_SIZE=2048

OPTION=$1
JACK_CLIENT=$2


function killpulse {
	echo "Killing pulseaudio..."
	echo "suspend 1" | pacmd
}

function run_jackd {
	echo "Running jackd in background with buffer size $BUFFER_SIZE..."
	jackd -d alsa --device hw:1 --rate 44100 --period $BUFFER_SIZE \
		&>/tmp/jackd.out &
}

function run_mymidi {
	echo "Running my midi app"
	python "$pmc"/core/MidiComposer.py 
}
function t { run_mymidi; }

case $OPTION in
	start )
		if pgrep jackd && pgrep $JACK_CLIENT
		then
			echo "Audio servers already running."
		else
			killpulse
			run_jackd
			sleep 1
			cd "$rosetus"
			make $JACK_CLIENT
			./$JACK_CLIENT 
			sleep 1
			if pgrep jackd && pgrep $JACK_CLIENT
			then
				echo "Audio servers started successfully."
			else
				echo "There was a problem starting the audio servers."
			fi
		fi

		run_mymidi
		echo "Use shell function >>t<< to run some midi shit..."
		;;
	stop )
		killall $JACK_CLIENT
		killall jackd
		echo Audio servers stopped.
		;;
	* )
		echo Please specify start or stop...
		;;
esac
