#ifndef ACTION
#define ACTION

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#define MAX_PARAMS_NUM 2



struct Action {
	int timeIndex;
	int noteX;
	int noteY;
	enum ActionType {
		attackNote = 0,
		releaseNote = 1,
		bendNote = 2,
	};
	ActionType actionType;
	int paramsUsed = 0;
	float params[MAX_PARAMS_NUM];

	operator std::string () {
		using namespace std;
		std::stringstream ss;

		ss << "Action object  <-  [" 
			<< timeIndex << " " 
			<< noteX << " " 
			<< noteY << " " 
			<< actionType;

		if (paramsUsed > 0)
			ss << " |";
		for (int i = 0; i < paramsUsed; ++i)
			ss << " " << params[i];
		ss << "]" << endl;
		return ss.str();
	}
};

#endif