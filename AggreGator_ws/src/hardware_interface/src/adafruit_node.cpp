#include "ros/ros.h"
#include "AdaFruit.h"
#include "motor_controller/AdaCmd.h"
#include "hardware_interface/WriteI2C.h"
#define adafruitAddress 0x60

ros::Subscriber sub;
ros::Publisher write_pub;

//Function writes and sends out messages of WriteI2C type. Contains data that sets the PWM value on the Adafruit hardware
void setWheelMotorI2C(const motor_controller::AdaCmd& msg)
{
		hardware_interface::WriteI2C wheelMotor; //Create message object
		
		pwmRegisterData LF = setLeftFrontMotor(msg.value[0]); //Declare structures containing data to be loaded into the relevant PWM channels
		pwmRegisterData LR = setLeftRearMotor(msg.value[1]);
		pwmRegisterData RR = setRightRearMotor(msg.value[2]);
		pwmRegisterData RF = setRightRearMotor(msg.value[3]);
		
		wheelMotor.addr = adafruitAddress; //I2C Address of the AdaFruit PWM generator
		
		
	//left front motor values
	for(int i = 0; i < 2; i++)		//iterates through LOW ON register for the left front motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(LF.lowRegOn[i]);

		write_pub.publish(wheelMotor); //Publish wheelMotor on accompanying topic
		
	for(int i = 0; i < 2; i++)	//iterates through HIGH ON register for the left front motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(LF.highRegOn[i]);

		write_pub.publish(wheelMotor); //Publish wheelMotor on accompanying topic
		
	for(int i = 0; i < 2; i++)	//iterates through LOW OFF register for the left front motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(LF.lowRegOff[i]);
			
		write_pub.publish(wheelMotor); //Publish wheelMotor on accompanying topic
	
	for(int i = 0; i < 2; i++)	
		wheelMotor.data.push_back(LF.highRegOff[i]); //iterates through HIGH OFF register for the left front motor and writes the data to the message, wheelMotor
			
		write_pub.publish(wheelMotor);//Publish wheelMotor on accompanying topic
			
	//left rear motor values
	for(int i = 0; i < 2; i++) //iterates through LOW ON register for the left rear motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(LR.lowRegOn[i]);
		
		write_pub.publish(wheelMotor); //Publish wheelMotor on accompanying topic
		
	for(int i = 0; i < 2; i++) //iterates through HIGH ON register for the left rear motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(LR.highRegOn[i]);
		
		write_pub.publish(wheelMotor);
		
	for(int i = 0; i < 2; i++)	//iterates through LOW OFF register for the left rear motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(LR.lowRegOff[i]);
		
		write_pub.publish(wheelMotor);
		
	for(int i = 0; i < 2; i++) //iterates through HIGH OFF register for the left rear motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(LR.highRegOff[i]);
		
		write_pub.publish(wheelMotor);
		
	//right rear motor values
	for(int i = 0; i < 2; i++)	//iterates through LOW ON register for the right rear motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(RR.lowRegOn[i]);
			
		write_pub.publish(wheelMotor);
	
	for(int i = 0; i < 2; i++)	//iterates through HIGH ON register for the right rear motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(RR.highRegOn[i]);
			
		write_pub.publish(wheelMotor);
	
	for(int i = 0; i < 2; i++)	//iterates through LOW OFF register for the right rear motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(RR.lowRegOff[i]);
			
		write_pub.publish(wheelMotor);
			
	for(int i = 0; i < 2; i++)	//iterates through HIGH OFF register for the right rear motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(RR.highRegOff[i]);
			
		write_pub.publish(wheelMotor);
			
	//right front motor values
	for(int i = 0; i< 2; i++)	//iterates through LOW ON register for the right front motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(RF.lowRegOn[i]);
			
		write_pub.publish(wheelMotor);
	
	for(int i = 0; i < 2; i++)	//iterates through HIGH ON register for the right front motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(RF.highRegOn[i]);
			
		write_pub.publish(wheelMotor);
				
	for(int i = 0; i < 2; i++)	//iterates through LOW OFF register for the right front motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(RF.lowRegOff[i]);
			
		write_pub.publish(wheelMotor);

	for(int i = 0; i < 2; i++)	//iterates through HIGH OFF register for the right front motor and writes the data to the message, wheelMotor
		wheelMotor.data.push_back(RF.highRegOff[i]);
			
		write_pub.publish(wheelMotor);
		
}
//Function that writes data to WriteI2C message, which will be used to set the PWM onthe AdaFruit hardware for the bucket drum motor
void setBucketMotorI2C(const motor_controller::AdaCmd& msg)
{
		hardware_interface::WriteI2C bucketMotor; //Create bucketMotor message
		bucketMotor.addr = adafruitAddress; //Sets the addr field as the AdaFruit's address on the I2C bus
		pwmRegisterData BD = setBucketDrum(msg.value[0]); //Declare structure which contains data which will be sent to the AdaFruit hardware to configure the PWM for the bucket drum motor
		
		//bucket drum motor values
		for(int i = 0; i < 2; i++)  //iterates through LOW ON register for the bucket drum motor and writes the data to the message, bucketMotor
			bucketMotor.data.push_back(BD.lowRegOn[i]);
			
			write_pub.publish(bucketMotor);
			
		for(int i = 0; i < 2; i++) //iterates through HIGH ON register for the bucket drum motor and writes the data to the message, bucketMotor
			bucketMotor.data.push_back(BD.highRegOn[i]);
			
			write_pub.publish(bucketMotor);
			
		for(int i = 0; i < 2; i++) //iterates through LOW OFF register for the bucket drum motor and writes the data to the message, bucketMotor
			bucketMotor.data.push_back(BD.lowRegOff[i]);
			
			write_pub.publish(bucketMotor);
			
		for(int i = 0; i < 2; i++) //iterates through HIGH OFF register for the bucket drum motor and writes the data to the message, bucketMotor
			bucketMotor.data.push_back(BD.highRegOff[i]);
			
			write_pub.publish(bucketMotor);
				
}
//Function that writes data to WriteI2C message, which will be used to set the PWM onthe AdaFruit hardware for the linear actuators
void setLinearActuatorI2C(const motor_controller::AdaCmd& msg)
{	
		hardware_interface::WriteI2C linearActuator;//Create linearActuator message
		linearActuator.addr = adafruitAddress; //Sets the addr field as the AdaFruit's address on the I2C bus
		
		pwmRegisterData LA = setLinearActuator(msg.value[0]); //Declare structure which contain data which will be sent to the AdaFruit hardware to configure the PWM for the linear actuators.
		
		//linear actuator motor values
		for(int i = 0; i < 2; i++) //iterates through LOW ON register for the linear actuator and writes the data to the message, linearActuator
			linearActuator.data.push_back(LA.lowRegOn[i]);
			
			write_pub.publish(linearActuator);
			
		for(int i = 0; i < 2; i++) //iterates through HIGH ON register for the linear actuator motor and writes the data to the message, linearActuator
			linearActuator.data.push_back(LA.highRegOn[i]);
			
			write_pub.publish(linearActuator);
			
		for(int i = 0; i < 2; i++) //iterates through LOW OFF register for the linear actuator and writes the data to the message, linearActuator
			linearActuator.data.push_back(LA.lowRegOff[i]);
			
			write_pub.publish(linearActuator);
			
		for(int i = 0; i < 2; i++) //iterates through HIGH OFF register for the linear actuator and writes the data to the message, linearActuator
			linearActuator.data.push_back(LA.highRegOff[i]);
			
			write_pub.publish(linearActuator);
}
//Writes messages that initialize the AdaFruit hardware, by clearing all PWM channels and setting the necessary modes.
void initialize()
{
		hardware_interface::WriteI2C init; //Create init message
		
		init.addr = adafruitAddress; //Sets the addr field as the AdaFruit's address on the I2C bus
		
		pwmRegisterData initialize = AdaFruitInit(); //Declare structure to load values into
	
	for(int i = 0; i < 2; i++) //iterates through initializing data and saves it to the init message
		init.data.push_back(initialize.initData[i]);
		
		write_pub.publish(init);
}

//Callback function
void adaFruitCallBack(const motor_controller::AdaCmd& msg)
{

		ROS_INFO("Receiving message: [%i] ",msg.device);
		switch(msg.device) //Checks device marker in incoming message
		{
		case motor_controller::AdaCmd::wheelMotors: //If wheelMotors, publish data relating to the wheel motors
			setWheelMotorI2C(msg);
			break;
		case motor_controller::AdaCmd::bucketDrum: //If bucketDrum,publish data relating to the bucket drum motor
			setBucketMotorI2C(msg);
			break;
		case motor_controller::AdaCmd::linearActuator: //If linearActuator, publish data relating to the linear actuators
			setLinearActuatorI2C(msg);
			break;
		default:
			ROS_INFO("Received message does not contain a legitimate device parameter"); //If no known device is in incoming message, output an error message
			break;
		}
}

int main(int argc, char** argv)
{
    AdaFruitInit(); //Initialize the adafruit node
    
    ros::init(argc, argv, "adafruit_node");

    //Node handler this is how you work with ROS
    ros::NodeHandle n;

	sub = n.subscribe("adaFruit", 1000, adaFruitCallBack);
	write_pub = n.advertise<hardware_interface::WriteI2C>("write_i2c",1000);
	//ros::Publisher write_register_pub = n.advertise<hardware_interface::WriteI2CRegister>("write_i2c_register",1000);
	
    ros::spin();
	
}
