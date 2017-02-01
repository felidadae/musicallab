source tools.sh
pulseaudio -k
run_jackd
sleep 1
slgui &
sleep 1
jmess -c ~/file.xml

