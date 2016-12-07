sudo apt-get install jackd2

sudo apt install sox
sudo gpasswd -a $USER audio
sudo apt-get install fluidsynth
sudo pip install mido

INSTALL_CADENCE=0
if [[ $INSTALL_CADENCE == "1" ]]; then
	#Read:
	# http://www.jackaudio.org/faq/pulseaudio_and_jack.html
	# https://github.com/jackaudio/jackaudio.github.com/wiki/WalkThrough_User_PulseOnJack
	#http://kxstudio.linuxaudio.org/Repositories
	#
	#Run cadence and:
	# and set ALSA Audio -> Using PulseAudio plugin bridge 
	# PulseAudio -> PulseAudio is started and bridged to JACK

	# Install required dependencies if needed
	sudo apt-get install apt-transport-https software-properties-common wget

	# Download package file
	wget https://launchpad.net/~kxstudio-debian/+archive/kxstudio/+files/kxstudio-repos_9.3.0~kxstudio1_all.deb

	# Install it
	sudo dpkg -i kxstudio-repos_9.3.0~kxstudio1_all.deb
	rm kxstudio*
fi
