#ifndef ACTION_CALLER
#define ACTION_CALLER

#include "../Synth.h"
#include "Action.h"



struct ActionCaller {
	ActionCaller( 
		Synth& synth, 
		std::vector<Action>& actions, 
		int& timeIndex ):
		synth(synth),
		actions(actions),
		timeIndex(timeIndex) 
	{}

	void call() {
		while (  actions[currAction].timeIndex == timeIndex  ) {
			int noteX = actions[currAction].noteX;
			int noteY = actions[currAction].noteY;
			float param1 = actions[currAction].params[0];
			float param2 = actions[currAction].params[1];

			switch(actions[currAction].actionType){
				case Action::ActionType::attackNote:
					synth.attackNote(noteX, noteY);
					break;
				case Action::ActionType::releaseNote:
					synth.releaseNote(noteX, noteY);
					break;
				case Action::ActionType::bendNote:
					synth.bendNote(noteX, noteY, param1, param2);
					break;

				default:
					throw std::exception();
			}

			++currAction;
		} 
	}

	void reset() {
		currAction = 0;
	}

private:
	int currAction = 0;
	Synth& synth;
	std::vector<Action>& actions;
	int& timeIndex; 
};
#endif