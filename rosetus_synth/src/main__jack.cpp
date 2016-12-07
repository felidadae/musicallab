#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// -----
#include <jack/jack.h>
#include <jack/midiport.h>
// -----
#include "FelidadaeSineSynth/Synth.h"
#include "FelidadaeSineSynth/Tuner.h"
// -----
#include "FelidadaeSineSynth/InputSynthData/ActionCaller.h"
#include "FelidadaeSineSynth/InputSynthData/InputDataReader.h"



jack_port_t *input_port;
jack_port_t *output_port;
jack_port_t *output_port2;

Tuner tuner(5,5);
Synth synth(tuner);
int timeIndex = 0;
//---
InputDataReader inputDataReader("/home/felidadae/Programming/Labs/MusicalLab/RosetusSynth/src/FelidadaeSineSynth/InputSynthData/interestingSin.tsv");
ActionCaller actionCaller(synth, inputDataReader.lastActions_, timeIndex);



int process(jack_nframes_t nframes, void *arg)
{
	void* port_buf = jack_port_get_buffer(input_port, nframes);  
	jack_default_audio_sample_t *out = 
		(jack_default_audio_sample_t *) jack_port_get_buffer (output_port, nframes);
	jack_default_audio_sample_t *out2 = 
		(jack_default_audio_sample_t *) jack_port_get_buffer (output_port2, nframes);
	
	FelidadaeAudio::AudioInOutBuffers<float_type> audioBlocks;
	audioBlocks.channelLength_ = nframes;
	audioBlocks.numOfChannels_ = 1;
	audioBlocks.out_.data_ = out;

	actionCaller.call();
	synth.process(audioBlocks);
	for (int i = 0; i < nframes; ++i)
		out2[i] = out[i];
	
	++timeIndex;
	printf("%d <-  %f\n", timeIndex, out[0]);

	return 0;
}

int srate(jack_nframes_t nframes, void *arg)
{
	printf("the sample rate is now %" PRIu32 "/sec\n", nframes);
	
	return 0;
}

void jack_shutdown(void *arg)
{
	printf("Exit jack client.");
	exit(1);
}

int main(int narg, char **args)
{
	jack_client_t *client;
	if ((client = jack_client_open ("midisine", JackNullOption, NULL)) == 0)
	{
		fprintf(stderr, "jack server not running?\n");
		return 1;
	}

	jack_set_process_callback (client, process, 0);
	jack_set_sample_rate_callback (client, srate, 0);
	jack_on_shutdown (client, jack_shutdown, 0);

	input_port = jack_port_register (client, "midi_in", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
	if (input_port == NULL)
		printf("Input port is NULL");
	output_port = jack_port_register  (client, "audio_out",  JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
	output_port2 = jack_port_register (client, "audio_out2", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

	if (jack_activate (client))
	{
		fprintf(stderr, "cannot activate client");
		return 1;
	}
	sleep(1);

	const char **ports;
	if ((ports = jack_get_ports (client, NULL, NULL, JackPortIsOutput)) == NULL) {
		fprintf(stderr, "Cannot find any physical capture ports\n");
		exit(1);
	}
	if (jack_connect (client, ports[0], jack_port_name (input_port))) {
		fprintf (stderr, "cannot connect input ports\n");
	}
	free (ports);
	if ((ports = jack_get_ports (client, NULL, NULL, JackPortIsInput)) == NULL) {
		fprintf(stderr, "Cannot find any physical playback ports\n");
		exit(1);
	}
	if (jack_connect (client, jack_port_name (output_port), ports[0])) {
		fprintf (stderr, "cannot connect output ports\n");
	}
	if (jack_connect (client, jack_port_name (output_port2), ports[1])) {
		fprintf (stderr, "cannot connect output ports\n");
	}
	free (ports);

	while(1)
	{
		sleep(1);
	}
	jack_client_close(client);
	exit (0);
}
