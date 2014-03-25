#include "ros/ros.h"
#include "std_msgs/builtin_int16.h"
#include "motor_controller/I2CGeneric.h"
#include "hardware_interface/GPIO.h"

ros::Subscriber sub;
ros::Publisher pub;

motor_controller::I2CGeneric GenerateMSG(int setpoint)
{
    motor_controller::I2CGeneric msg;
    //Set msg addr
    //msg.addr = ???;           //Use an enumerated type from the I2C node

    //Set the msg data
    msg.data = setpoint;

    return msg;
}


//Function that controls the direction of the motors using the GPIO pins on the O-Droid
void setMotorDirection(std_msgs::Int16 input)
{
	if(input.data == 0) //Brake to GND, write 0 to every pin
	{
		setGPIOWrite(33,0);
		setGPIOWrite(31,0);
	}
	else if(input.data > 0) //INA = GPIO pin 33, INB = GPIO pin 31, linear actuator moves up
	{
		setGPIOWrite(33,1); 
		setGPIOWrite(31,0);
	}
	else //Linear actuator moves down
	{
		setGPIOWrite(33,0);
		setGPIOWrite(31,1);
	}
	
}

motor_controller::I2CGeneric LinearActuatorPID(int setpoint)
{
    /*
     * This is where the pid controller goes
     */

    return GenerateMSG(setpoint);               //Output the msg NOTE: change the passed parameter do not use setpoint directly
}

void SetSetpoint(const std_msgs::Int16& msg)
{
    setMotorDirection(msg);
    pub.publish(LinearActuatorPID(msg.data));   //Generate and publish an I2C msg
}

//MAIN
int main(int argc, char** argv)
{
    ros::init(argc, argv, "linear_actuator_node");                              //Initialize node
    ros::NodeHandle n;                                                          //Create nodehandle object

    sub = n.subscribe("linear_actuator_rc", 1000, SetSetpoint);                 //Create object to subscribe to topic "linear_actuator_rc"
    pub = n.advertise<motor_controller::I2CGeneric>("I2C",1000);                    //Create object to publish to topic "I2C"
	
    //Loop as long as ros system is ok
    ros::spin();

	
	return 0;
}
