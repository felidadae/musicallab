GCC := g++ -g -std=c++11 
LIB_FLAGS := `pkg-config --cflags --libs jack` -I /src/
DIR_BIN := bin
DIR_BUILD := build
DIR_SRC := src
SHELL := /bin/bash



all: sampleClient

sampleClient: SampleJackClient.c
	g++ SampleJackClient.c $(LIB_FLAGS)

mysynth: $(DIR_BIN)/mysynth
	cp $(DIR_BIN)/mysynth .

$(DIR_BIN)/mysynth: $(DIR_BUILD)/Synth.o $(DIR_BUILD)/main__jack.o
	$(GCC) -o $@ $+ $(LIB_FLAGS)

$(DIR_BUILD)/Synth.o: $(DIR_SRC)/FelidadaeSineSynth/Synth.cpp
	$(GCC) -o $@ -c $< -I /src/

$(DIR_BUILD)/main__jack.o: $(DIR_SRC)/main__jack.cpp
	$(GCC) -o $@ -c $< -I /src/
