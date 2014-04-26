#include "ros/ros.h"
#include "std_msgs/builtin_int16.h"
#include "motor_controller/AdaCmd.h"
#include "hardware_interface/GPIO.h"
#include "controller.h"
ros::Subscriber sub;
ros::Publisher pub;
int controlInput;

//Timing variables
ros::Time last_time(0), current_time;
ros::Duration update_rate(0.01);       //time in seconds between sends

SSController linearActuator; //create controller object for the linear actuator
	
enum
{
	LA_A = 40,
	LA_B = 42
};


float controlFunction() //WARNING: CONTROL USED BELOW WERE DESIGNED FOR WHEEL MOTORS, THIS IS JUST HERE FOR PLACE HOLDER UNTIL LINEAR 				ACTUATOR DESIGN IS DEVELOPED
{
	//Linear actuator controller goes here!!!!

	linearActuator.setU(controlInput);
	
	int iterations = 0; //Number of iterations to update control outputs
	
	float controlOutput;
	while(iterations < 100) //Updates 100 times before accepting new values to update on and then sends out updated values on 					controlOutput
	{
		linearActuator.update();
		
	  	controlOutput = (linearActuator.getY()[0][0]/24)*100; //Does some scaling on the control output values to get PWM value for AdaFruit downstream


		iterations++; //Increments iterations variable
	}
	return controlOutput;
}

//Function that controls the direction of the motors using the GPIO pins on the O-Droid
void setMotorDirection(int la)
{
	if(la == 0) //Brake to GND, write 0 to every pin
	{
		setGPIOWrite(LA_A,0);
		setGPIOWrite(LA_B,0);
	}
	else if(la > 0) //INA = GPIO pin 40, INB = GPIO pin 42, linear actuator moves up
	{
		setGPIOWrite(LA_A,1); 
		setGPIOWrite(LA_B,0);
	}
	else //Linear actuator moves down
	{
		setGPIOWrite(LA_A,0);
		setGPIOWrite(LA_B,1);
	}
	
}


motor_controller::AdaCmd generateMessage()
{
    motor_controller::AdaCmd msg;
    
    msg.device = motor_controller::AdaCmd::linearActuator;

    msg.value.push_back(controlFunction());

    return msg;
}


void callBack(const std_msgs::Int16& msg)
{
    controlInput = abs(msg.data)*24/32767;//Scales input to be an equivalent voltage input to motor controller
	
    setMotorDirection(msg.data);

 
}

//MAIN
int main(int argc, char** argv)
{
    ros::init(argc, argv, "linear_actuator_node");                     //Initialize node
    ros::NodeHandle n;                                                 //Create nodehandle object

    sub = n.subscribe("linear_actuator_rc", 1000, callBack);           //Create object to subscribe to topic "linear_actuator_rc"
    pub = n.advertise<motor_controller::AdaCmd>("adaFruit",1000);      //Create object to publish to topic "adaFruit"
	
   while(true)
	{
		//Update time
		current_time = ros::Time::now();
		//Check if interval has passed
		if(current_time - last_time > update_rate)
		{
			//Reset time
			last_time = current_time;
			if(sub.getNumPublishers() == 0) //In case of loss of connection to publisher, set controller inputs to 0
				controlInput = 0.0;
			//motor_controller function
			controlFunction();
			while(pub.getNumSubscribers()==0);//Prevents message from sending when publisher is not completely connected to subscriber.
			pub.publish(generateMessage());
		}
		ros::spinOnce();
	}

    resetGPIO();

    return 0;
}
