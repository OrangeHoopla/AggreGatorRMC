#include "ros/ros.h"
#include <sensor_msgs/Joy.h>
#include "remote_control/WheelMotor.h"
#include <std_msgs/builtin_int16.h>
#include "ros/time.h"
#include "ros/duration.h"
#include <string.h>

/*
 * Variables
 */
int running_avg = 0;
double left_motors(0.0), right_motors(0.0);
double bucket_motor(0.0), linear_actuator(0.0);
short int bucket_motor_dir(1), linear_actuator_dir(1);
bool motion_enable = false;			//If this is zero msgs will be published

//Keep track of button presses (to find button releases)
bool left_bumper_pressed = false;
bool right_bumper_pressed = false;
bool start_pressed = false;

//Timing variables
ros::Time last_time, current_time;
ros::Duration send_time(0.1);       //time in seconds between sends

//Ros publishers and subscribers
ros::Publisher wheel_motor_pub;
ros::Publisher linear_actuator_pub;
ros::Publisher bucket_motor_pub;

/*
 * Int for mapping
 * 1 is linear, 2 is quadratic, 3 cubic (anything else defaults to linear
 */
int32_t mapping;

//Buttons on the Xbox Controller
enum XboxButtons
{
    A,
    B,
    X,
    Y,
    LB,
    RB,
    BACK,
    START,
    POWER,
    LEFT_STICK,
    RIGHT_STICK
};

/*
 * LR = left right
 * UD = up down
 * Left = left stick
 * Right = right stick
 * RT = right trigger
 * LT = left trigger
 */
enum XboxAxis
{
    LR_LEFT,
    UD_LEFT,
    LT,
    LR_RIGHT,
    UD_RIGHT,
    RT
};

/*
 * Forward declarations
 */
void StopEverything();

/*
 * Write the motor msg out
 * Rights the current command out
 * IN: none
 * Out: WheelMotor to wheel_motor_rc topic
 */
void WriteMotorValue()
{
    if(motion_enable)
    {
	    //Update time
	    current_time = ros::Time::now();
	    if(current_time - last_time > send_time)
	    {
		//reset time
		last_time = current_time;
		//reset running avg
		running_avg = 0;

		//Format data
		remote_control::WheelMotor wheel_msg;

		int left = left_motors * 32767;       //Scale to signed 16 bit int
		int right = right_motors * 32767;     //Scale to signed 16 bit int
		wheel_msg.LF_motorVal = left;
		wheel_msg.LR_motorVal = left;
		wheel_msg.RR_motorVal = right;
		wheel_msg.RF_motorVal = right;

		//Format actuator and bucket drum data
		/*
		 *      LT and RT are maped to:
		 *          not pressed = 1
		 *          half = 0
		 *          full pressed = -1
		 *      Transform to:
		 *          not pressed = 0
		 *          half = 16384
		 *          full pressed = 32767
		 *      Math:
		 *          value -= 1
		 *          value /= -2
		 *          value *= 32767
		 *
		 *          Subtract one from the scale factor so that we do not go over(-16383)
		 *
		 *      Make positive or negative based on booleans:
		 *          value *= direction
		 *          direction = 1 or -1 based on LB and RB
		 */
		int actuator = (linear_actuator - 1) * -16383 * linear_actuator_dir;
		int bucket = (bucket_motor - 1) * -16383 * bucket_motor_dir;

		std_msgs::Int16 actuator_msg, bucket_msg;
		actuator_msg.data = actuator;               //Float -> int
		bucket_msg.data = bucket;                   //Float -> int

		/*Debug
		ROS_INFO("Wheel_Motor_rc, LF: %i, LB: %i, RB: %i, FR: %i", 
			wheel_msg.LF_motorVal,
			wheel_msg.LR_motorVal,
			wheel_msg.RR_motorVal,
			wheel_msg.RF_motorVal);

		ROS_INFO("Linear_rc: %i", actuator_msg.data);
		ROS_INFO("Bucket_rc: %i", bucket_msg.data);*/
	
		//Send msg
		wheel_motor_pub.publish(wheel_msg);
		linear_actuator_pub.publish(actuator_msg);
		bucket_motor_pub.publish(bucket_msg);
	    }
     }
     else	//If motion is not enabled stop everything
     {
	StopEverything();
     }
}

/*
 * Average motor input
 * Takes a runing average of the remote control input
 * ((count - 1) * last_value + current_value) / count
 * the count must be kept externaly
 * IN: left motor setpoint, right motor setpoint
 * Out: Sets global variables to the average
 */
void AvgMotorInput(float left, float right, float bucket, float actuator)
{
    /*
     * Set up mapping (Quite easy since values are already scaled to -1 to 1)
     * linear
     *      No change required
     * Quadratic:
     *      value *= value
     *      for negative orignal values * -1
     * Cubic:
     *      value = value^3
     */
    if(mapping % 2)
    {
        left        = pow(left, mapping);
        right       = pow(right, mapping);
        //bucket      = pow(bucket, mapping);
        //actuator    = pow(actuator, mapping);
    }
    else
    {
        left        = pow(left, mapping)     * ((left >= 0) ? 1 : -1);
        right       = pow(right, mapping)    * ((right >= 0) ? 1 : -1);
        //bucket      = pow(bucket, mapping)   * ((bucket >= 0) ? 1 : -1);
        //actuator    = pow(actuator, mapping) * ((actuator >= 0) ? 1 : -1);
    }

    /*
     *Take a running Avg
     * NewAvg = ((count - 1) * lastAvg + newValue) / count
     */

    if(running_avg)
    {
        left_motors = ((running_avg - 1) * left_motors + left) / running_avg;
        right_motors = ((running_avg - 1) * right_motors + right) / running_avg;
        bucket_motor = ((running_avg - 1) * bucket_motor + bucket) / running_avg;
        linear_actuator = ((running_avg - 1) * linear_actuator + actuator) / running_avg;
    }
    else //Set to first value after last send
    {
        left_motors = left;
        right_motors = right;
        bucket_motor = bucket;
        linear_actuator = actuator;
    }
    //Increment running_avg
    running_avg++;
}

void XboxCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
    //Check for button releases
    if(right_bumper_pressed & !joy->buttons[RB])
    {
        linear_actuator_dir *= -1;
        right_bumper_pressed = false;
    }
    else if(joy->buttons[RB])
    {
        right_bumper_pressed = true;
    }

    if(left_bumper_pressed & !joy->buttons[LB])
    {
        bucket_motor_dir *= -1;
        left_bumper_pressed = false;
    }
    else if(joy->buttons[LB])
    {
        left_bumper_pressed = true;
    }

    if(start_pressed & !joy->buttons[START])
    {
	//Debug
    	ROS_INFO("Start pressed");

	motion_enable = !motion_enable;
	//If we disable input imediatly send a stop msg
	if(!motion_enable)
		StopEverything();
	
	start_pressed = false;
    }
    else if(joy->buttons[START])
    {
	start_pressed = true;
    }

    //average the inputs
    AvgMotorInput(joy->axes[UD_LEFT], joy->axes[UD_RIGHT], joy->axes[LT], joy->axes[RT]);
}

//StopEverything
//Publishes all zero messages to all motors
void StopEverything()
{
    //Debug
    //ROS_INFO("Stop Everything!");

    //Generate msgs
    //Format data
    remote_control::WheelMotor wheel_msg;
    std_msgs::Int16 actuator_msg, bucket_msg;

    //Fill msgs with 0s
    wheel_msg.LF_motorVal = 0;
    wheel_msg.LR_motorVal = 0;
    wheel_msg.RR_motorVal = 0;
    wheel_msg.RF_motorVal = 0;
    actuator_msg.data = 0;
    bucket_msg.data = 0;

    //Send msg
    wheel_motor_pub.publish(wheel_msg);
    linear_actuator_pub.publish(actuator_msg);
    bucket_motor_pub.publish(bucket_msg);
}

int main(int argc, char** argv)
{
    /*
     * Initilization
     */

    //Initilize the remote control node
    ros::init(argc, argv, "remote_control_node");

    //Node handler this is how you work with ROS
    ros::NodeHandle n;

    //Get the parameters
    //Send frequence
    double temp;
    n.param<double>("/remote_control/send_freq", temp, 0.1);
    send_time.fromSec(1 / temp);
    //ROS_INFO("Setting send period to %f, (frequency: %f)", send_time.toSec(), temp);

    //mapping
    n.param<int32_t>("/remote_control/xbox_controller/mapping", mapping, 1);
    if(mapping < 1 || mapping > 3)
        mapping = 1;

    //ROS_INFO("Xbox controller set to order %i mapping", mapping);

    //Set up subscriber, listens to joy topic, buffer only 10 messages, us XboxCallback
    ros::Subscriber joy_sub = n.subscribe<sensor_msgs::Joy>("joy", 1000, XboxCallback);

    //Set up publisher on motor_rc, buffer up to 1000 msgs
    wheel_motor_pub = n.advertise<remote_control::WheelMotor>("wheel_motor_rc", 1000);

    //Set up publisher on linear_actuator_rc
    linear_actuator_pub = n.advertise<std_msgs::Int16>("linear_actuator_rc", 1000);

    //Set up publisher on bucket_motor_rc
    bucket_motor_pub = n.advertise<std_msgs::Int16>("bucket_motor_rc", 1000);

    //Initilize time
    last_time = ros::Time::now();
    current_time = last_time;

    //Wait for publishers to inti then turn everything off
    while(bucket_motor_pub.getNumSubscribers() == 0 || linear_actuator_pub.getNumSubscribers() == 0 || wheel_motor_pub.getNumSubscribers() == 0);
    StopEverything();


    /*
     * Main loop
     */
    while (ros::ok())
    {
        WriteMotorValue();
        ros::spinOnce();
    }
}
