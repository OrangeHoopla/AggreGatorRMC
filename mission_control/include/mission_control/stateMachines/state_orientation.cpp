#include "state_orientation.h"

OrientationState::OrientationState(States state){
	//for initializing data members for the particular state
	switch(state){
		case ORIENTATION_START:
			std::cout << "ORIENTATION_START" << std::endl;
			break;

		case ORIENTATION_DUMP:
			std::cout << "ORIENTATION_DUMP" << std::endl;
			break;
	}
}

int OrientationState::orientToMine(){
	return 0;
}

int OrientationState::orientToDump(){
	return 0;
}