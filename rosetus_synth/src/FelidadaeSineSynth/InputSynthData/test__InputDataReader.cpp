#include "InputDataReader.h"
#include <iostream>
#include <cstdlib>

#define PINPUT "/home/felidadae/Programming/Labs/MusicalLab/RosetusSynth/InputSynthData/sample1.tsv"

int main() {
	using namespace std;

	InputDataReader reader;
	try {
		reader.read( PINPUT );
	}
	catch(const exception& e) {
		cout << e.what();
		exit(1);
	}

	return 0;
}
