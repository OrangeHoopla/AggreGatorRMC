#include "ros/ros.h"
#include "std_msgs/builtin_int16.h"
#include "motor_controller/I2CMSG.h"

void callback (const std_msgs::Int16& msg)
{

}

//MAIN
int main(int argc, char** argv)
{
	ros::init(argc, argv, "linear_actuator_node"); //Initialize node

	ros::NodeHandle n; //Create nodehandle object

	ros::Subscriber sub = n.subscribe("linear_actuator_rc", 1000, callback); //Create object to subscribe to topic "linear_actuator_rc"
	
	ros::Publisher pub = n.advertise<motor_controller::I2CMSG>("I2C",1000); //Create object to publish to topic "I2C"

	ros::Rate loop_rate(500); //Set frequency of looping. 10 Hz
	
	//Loop is true while ctrl-c isn't pressed, or ros::shutdown() has not been called, or the node has not been kicked off the network.
	while(ros::ok()){

		ros::spinOnce(); //Call the callback function
		
		loop_rate.sleep(); //Sleep for the time remaining to allot 10 Hz publishing rate.

	}

	
	return 0;
}
