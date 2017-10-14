#!/bin/bash -e
if_off=${1}
if [ "$if_off" == "--off" ]; then
	killall jackd
	sleep 1
	pulseaudio -D
	xrandr -s 3840x2160
else
	[ "$(pgrep jackd)" != "" ] && echo "Jackd already running" && exit
	xrandr -s 1920x1080
	sleep 2
	redshift -O 4400
	source tools.sh
	pulseaudio -k
	sleep 2
	run_jackd
	sleep 2
	slgui &
	sleep 2
	jmess -c ~/AudioLoops/jmess_exported.xml
fi
