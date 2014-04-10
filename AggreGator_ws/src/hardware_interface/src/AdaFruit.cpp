/*Daniel Kelly
UF AggreGator
	This contains definitions for the necessary interfacing functions to the Adafruit PWM generator, which will help control the motors
	*/
#include "AdaFruit.h"

using namespace std;

//Initializes the AdaFruit PWM generator by setting the MODE1 register accordingly.
void AdaFruitInit()
{
	init_i2c(); //Initializes the I2C bus
	
	char data[] = {0x0,0b00000001}; //Leave everything in MODE1 as default, except turn off SLEEP bit
	
	write_i2c(AdaFruitAddr,2,data); //Writes above data to the Adafruit
	
}


//Sets the PWM for the left front motor (assigned to PWM channel 3)
//Input is a percentage value
void setLeftFrontMotor(int PWM)
{
	
	int on_count = PWM * .01 * 4095; //Converts input to decimal and gets correct counter value
	char on_count_high = (char)(on_count/256); //Isolates higher 4 bits of count value
	char on_count_low = (char)(on_count & 255);//Isolates lower 8 bits of count value
	
	//Value for lower 8 bit ON register
	char lowRegOn[] = {leftFrontMotorChannel_ON_LOW,0}; //ON values are set to 0 so the counter turns 		ON at count value of 0, or at the beginning of the PWM cycle
	
	//Writes value to Adafruit
	write_i2c(AdaFruitAddr,2,lowRegOn);
	
	//Value for higher 8 bit register
	char highRegOn[] = {leftFrontMotorChannel_ON_HIGH,0};
	
	write_i2c(AdaFruitAddr,2,highRegOn);
	
	//Value for lower 8 bit OFF register
	char lowRegOff[] = {leftFrontMotorChannel_OFF_LOW,on_count_low};//Sets the count values for the PWM to turn OFF
	
	write_i2c(AdaFruitAddr,2,lowRegOff);
	
	//Value for higher 8 bit OFF register
	char highRegOff[] = {leftFrontMotorChannel_OFF_HIGH,on_count_high};
	write_i2c(AdaFruitAddr,2,highRegOff);
	
}
//Sets the PWM for the left front motor (assigned to PWM channel 0)
//Input is a percentage value
void setLeftRearMotor(int PWM)
{
	
	int on_count= PWM * .01 *4095; //Converts input to decimal and gets correct counter value
	char on_count_high = (char)(on_count/256); //Isolates higher 4 bits of count value
	char on_count_low = (char)(on_count & 255); //Isolates lower 8 bits of count value
	
	//Value for lower 8 bit ON register
	char lowRegOn[] = {leftRearMotorChannel_ON_LOW,0};//ON values are set to 0 so the counter turns 		ON at count value of 0, or at the beginning of the PWM cycle
	write_i2c(AdaFruitAddr,2,lowRegOn);
	//Value for higher 8 bit register
	char highRegOn[] = {leftRearMotorChannel_ON_HIGH,0};
	write_i2c(AdaFruitAddr,2,highRegOn);
	//Value for lower 8 bit OFF register
	char lowRegOff[] = {leftRearMotorChannel_OFF_LOW,on_count_low};//Sets the count values for the PWM to turn OFF
	write_i2c(AdaFruitAddr,2,lowRegOff);
	//Value for higher 8 bit OFF register
	char highRegOff[] = {leftRearMotorChannel_OFF_HIGH,on_count_high};
	write_i2c(AdaFruitAddr,2,highRegOff);
	
}
//Sets the PWM for the left front motor (assigned to PWM channel 4)
//Input is a percentage value
void setRightRearMotor(int PWM)
{

	int on_count = PWM * .01 * 4095;//Converts input to decimal and gets correct counter value
	char on_count_high = (char)(on_count/16); //Isolates higher 4 bits of count value
	char on_count_low = (char)(on_count & 255);//Isolates lower 8 bits of count value
	//Value for lower 8 bit ON register
	char lowRegOn[] = {rightRearMotorChannel_ON_LOW,0};//ON values are set to 0 so the counter turns 		ON at count value of 0, or at the beginning of the PWM cycle
	write_i2c(AdaFruitAddr,2,lowRegOn);
	//Value for higher 8 bit register
	char highRegOn[] = {rightRearMotorChannel_ON_HIGH,0};
	write_i2c(AdaFruitAddr,2,highRegOn);
	//Value for lower 8 bit OFF register
	char lowRegOff[] = {rightRearMotorChannel_OFF_LOW,on_count_low};
	write_i2c(AdaFruitAddr,2,lowRegOff);
	//Value for higher 8 bit OFF register
	char highRegOff[] = {rightRearMotorChannel_OFF_HIGH,on_count_high};
	write_i2c(AdaFruitAddr,2,highRegOff);
	
}
//Sets the PWM for the left front motor (assigned to PWM channel 1)
//Input is a percentage value
void setRightFrontMotor(int PWM)
{


	int on_count = PWM * .01 * 4095;//Converts input to decimal and gets correct counter value
	char on_count_high = (char)(on_count/256);//Isolates higher 4 bits of count value
	char on_count_low = (char)(on_count & 255);//Isolates lower 8 bits of count value
	//Value for lower 8 bit ON register
	char lowRegOn[] = {rightFrontMotorChannel_ON_LOW,0};//ON values are set to 0 so the counter turns 		ON at count value of 0, or at the beginning of the PWM cycle
	write_i2c(AdaFruitAddr,2,lowRegOn);
	//Value for higher 8 bit register
	char highRegOn[] = {rightFrontMotorChannel_ON_HIGH,0};
	write_i2c(AdaFruitAddr,2,highRegOn);
	//Value for lower 8 bit OFF register
	char lowRegOff[] = {rightFrontMotorChannel_OFF_LOW,on_count_low};//Sets the count values for the PWM to turn OFF
	write_i2c(AdaFruitAddr,2,lowRegOff);
	//Value for higher 8 bit OFF register
	char highRegOff[] = {rightFrontMotorChannel_OFF_HIGH,on_count_high};
	write_i2c(AdaFruitAddr,2,highRegOff);
	
}
//Sets the PWM for the bucket drum motor (asssigned to PWM channel 5)
//Input is a percentage value
void setBucketDrum(int PWM)
{
	int on_count = PWM * .01 * 4095;//Converts input to decimal and gets correct counter value
	char on_count_high = (char)(on_count/256);//Isolates higher 4 bits of count value
	char on_count_low = (char)(on_count & 255);//Isolates lower 8 bits of count value
	//Value for lower 8 bit ON register
	char lowRegOn[] = {bucketDrumMotorChannel_ON_LOW,0};//ON values are set to 0 so the counter turns 		ON at count value of 0, or at the beginning of the PWM cycle
	write_i2c(AdaFruitAddr,2,lowRegOn);
	//Value for higher 8 bit register
	char highRegOn[] = {bucketDrumMotorChannel_ON_HIGH,0};
	write_i2c(AdaFruitAddr,2,highRegOn);
	//Value for higher 8 bit OFF register
	char lowRegOff[] = {bucketDrumMotorChannel_OFF_LOW,on_count_low};//Sets the count values for the PWM to turn OFF
	write_i2c(AdaFruitAddr,2,lowRegOn);
	
	char highRegOff[] = {bucketDrumMotorChannel_OFF_HIGH,on_count_high};
	write_i2c(AdaFruitAddr,2,highRegOff);

}

//Sets the PWM for the bucket drum motor (asssigned to PWM channel 2)
//Input is a percentage value
void setLinearActuator(int PWM)
{
	int on_count = PWM * .01 * 4095;//Converts input to decimal and gets correct counter value
	char on_count_high = (char)(on_count/256);//Isolates higher 4 bits of count value
	char on_count_low = (char)(on_count & 255);//Isolates lower 8 bits of count value
	//Value for lower 8 bit ON register
	char lowRegOn[] = {linearActuatorMotorChannel_ON_LOW,0};//ON values are set to 0 so the counter turns 		ON at count value of 0, or at the beginning of the PWM cycle
	write_i2c(AdaFruitAddr,2,lowRegOn);
	//Value for higher 8 bit register
	char highRegOn[] = {linearActuatorMotorChannel_ON_HIGH,0};
	write_i2c(AdaFruitAddr,2,highRegOn);
	//Value for higher 8 bit OFF register
	char lowRegOff[] = {linearActuatorMotorChannel_OFF_LOW,on_count_low};//Sets the count values for the PWM to turn OFF
	write_i2c(AdaFruitAddr,2,lowRegOn);
	
	char highRegOff[] = {linearActuatorMotorChannel_OFF_HIGH,on_count_high};
	write_i2c(AdaFruitAddr,2,highRegOff);

}
