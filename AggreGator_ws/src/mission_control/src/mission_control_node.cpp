#include <iostream>
#include <string>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "mission_control/mission_control.h"

using namespace std;

int main(int argc, char **argv){
	ros::init(argc, argv, "mission_control_node");
	MissionControl *mc = new MissionControl();
	cout << "Initialized MissionControl()" << endl;
	mc->Start();
	
	return 0;
}