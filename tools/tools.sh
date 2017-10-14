#Global tools
#
#

scriptPath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
projectRoot__=$scriptPath
font0=$labs/MusicalLab/resources/"FluidR3GM2-2.SF2"
font0=$labs/MusicalLab/resources/"HSSynth.sf2"


###
# Use that tools to kill and rerun pulseaudio,
# if You don't want to use brigde pulseaudio to jackd;
##
function kill_pulse {
	echo "Killing pulseaudio..."
	echo "suspend 1" | pacmd
}
function rerun_pulse {
	kill_audioInfrastructure
	pulseaudio -k
	pulseaudio -D 
}

function kill_audioInfrastructure {
	killall jackd
	killall fluidsynth
}
function reset_audioInfrastructure {
	kill_pulse
	kill_audioInfrastructure
	setAudioCardID 
	run_jackd
	sleep 2
	run_fluidsynth
	sleep 2
	run_mymidi
}
function setAudioCardID {
	# Here You should grep `aplay -l` for your audio card;
	AUDIO_CARD_ID=$(aplay -l | grep "NAMEOFCARD" | perl -lne 'if ($_ =~ /card (.)/) {print $1;}')
	if [[ $AUDIO_CARD_ID == "" ]]; then
		AUDIO_CARD_ID=2
	fi
}
export BUFFER_SIZE=64
function run_jackd {
	if [[ $(pgrep jackd) == "" ]]; then
		echo "Running jackd in background with buffer size $BUFFER_SIZE..."
		jackd -d alsa --device hw:$AUDIO_CARD_ID --rate 44100 --period $BUFFER_SIZE \
			&>/tmp/jackd.out &
	fi
	check_ jackd
}
function run_fluidsynth {
	if [[ $(pgrep fluidsynth) == "" ]]; then
		fluidsynth --server --no-shell --audio-driver=jack \
			--connect-jack-outputs --reverb=0 --chorus=0 --gain=0.3  \
			"$font0" \
			&>/tmp/fluidsynth.out &
		check_ fluidsynth
	fi
}
function run_fluidsynth_alsa {
	if [[ $(pgrep fluidsynth) == "" ]]; then
		fluidsynth --server --no-shell --audio-driver=alsa \
			--reverb=0.1 --chorus=0.1 --gain=0.3 -o audio.period-size=512 \
			"$font0" \
			&>/tmp/fluidsynth.out &
	fi
}

#Offline midi creation and playback
function playMidiByFluidSynth2 {
	#Plays midi by fluidsynth using directly alsa
	#using device
	local midifile=${1}

	fluidsynth --audio-driver=alsa -o \
		audio.alsa.device=hw:1 \
		"$font0" \
		"$midifile"	
}
function playMidiByFluidSynth {
	fluidsynth -o audio.period-size=512 -a alsa -m alsa_seq -l -i $font0 $1
}

function check_ {
	if pgrep $1 
	then
		echo $1 running.
	else
		echo There was a problem starting $1.
		exit
	fi
}
function pp-reload {
	source $projectRoot__/tools.sh 
}

#as initialise 
setAudioCardID
