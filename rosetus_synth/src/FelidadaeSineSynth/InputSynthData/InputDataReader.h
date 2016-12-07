#ifndef INPUT_DATA_READER
#define INPUT_DATA_READER

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Action.h"
#include <algorithm>



struct InputDataReader {
	std::vector<Action> lastActions_;

	InputDataReader() {}
	InputDataReader(std::string filename) {
		read(filename);
	}

	void read(std::string filename) {
		using namespace std;

		string line;
		ifstream myfile (filename.c_str());
		if (myfile.is_open())
		{
			getline (myfile,line);
			while ( getline (myfile,line) )
			{
				Action nextAction;

				std::stringstream   linestream(line);
				std::string         data;
				int                 val1;
				int                 val2;

				std::getline(linestream, data, '\t');
				nextAction.timeIndex = stoi(data);
				//---
				std::getline(linestream, data, '\t');
				nextAction.noteX = stoi(data);
				//---
				std::getline(linestream, data, '\t');
				nextAction.noteY = stoi(data);
				//---
				std::getline(linestream, data, '\t');
				nextAction.actionType = Action::ActionType(stoi(data));

				while ( std::getline(linestream, data, '\t') ) {
					nextAction.params[nextAction.paramsUsed++] = stof(data);
				}

				cout << string(nextAction);

				lastActions_.push_back( nextAction );
			}
			myfile.close();
		}
		else {
			cout << "BROBROBRO\n\n\n";
			throw std::exception();
		}
	}
};

#endif
