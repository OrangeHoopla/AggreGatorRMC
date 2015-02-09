#include <iostream>
#include <sstream>
#include "mission_control.h"
#include "mission_control/behaviors/behavior_map.h"

using namespace std;
//====================================================
//CONSTRUCTORS
//====================================================
/*-----------------------------------------	
 *	Default Constructor
 *		initialize debug and class_name
 *		creates an instance of all the handlers
 *-----------------------------------------*/
MissionControl::MissionControl(){
	this->debug = false;
	this->class_name = "[MISSION CONTROL]";
}

/*-----------------------------------------	
 *	Debug Constructor
 *		same as default constructor except
 *		can turn on debug mode, e.g. all if(debug) will run
 *-----------------------------------------*/
MissionControl::MissionControl(bool debug){
	this->debug = debug;
	this->class_name = "[MISSION CONTROL]";
}

//====================================================
//CALLBACKS
//====================================================
/*-----------------------------------------	
 *	MissionControlCallback
 *		
 *-----------------------------------------*/
void MissionControlCallback(const std_msgs::String::ConstPtr& msg){
	cout << msg->data.c_str() << endl;
}


//====================================================
//METHODS
//====================================================
/*-----------------------------------------	
 *	Start
 *		starts up everything
 *-----------------------------------------*/
void MissionControl::StartSenseAct(){
	int input;
	cout << "Ctrl-C to terminate." << endl;

	try {
		StateMachine *sm = new StateMachine();
		sm->start(WAIT);

	}catch(...){
		cout << "Some exception has occurred." << "\n";
	}

	//clean up anything here
}//end StartSenseAct
