#include "servo_array_driver/servo_array_driver_node.h"

servo_driver::servo_driver()
{
	//SUBSCRIBERS
	speed_sub = n.subscribe("/vehicle/speed_cmd", 1, &servo_driver::speed_callback, this);
	steer_sub = n.subscribe("/vehicle/steering_cmd", 1, &servo_driver::steer_callback, this);

	//PUBLISHERS
	servo_pub = n.advertise<servo_array_driver::ServoArray>("/servos_absolute", 1);

	//PARAMETERS
	n.param<double>("servo_array_driver_node/steer_0", steer_0, 330); //Nominal Steering Servo Value
	n.param<double>("servo_array_driver_node/speed_0", speed_0, 300); //Nominal Speed Servo Value
	n.param<double>("servo_array_driver_node/steer_range", steer_range, 20); //Steering Limit Window
	n.param<double>("servo_array_driver_node/speed_range", speed_range, 10); //Speed Limit Window

	//INITIALIZE VARIABLES
	steer = 0.0;
	speed = 0.0;

	//CONSTRUCTOR STATUS REPORT
	std::cout<<"------------------------------------"<<std::endl;
	std::cout<<"Servo Driver Initialized"<<std::endl;
	std::cout<<"Default Servo Values: "<<std::endl;
	std::cout<<"Steering: "<<steer_0<<"\tSpeed: "<<speed_0<<std::endl;
	std::cout<<"Servo Ranges: "<<std::endl;
	std::cout<<"Steering: "<<steer_range<<"\tSpeed: "<<speed_range<<std::endl;
	std::cout<<"------------------------------------"<<std::endl;
}

servo_driver::~servo_driver()
{
	std::cout<<std::endl<<"Servo Driver Shutdown"<<std::endl;
}

void servo_driver::speed_callback(const std_msgs::Float64::ConstPtr& speed_msg)
{
	speed = speed_msg->data;
	std::cout<<"Recieved Speed Command: "<<speed<<std::endl;
}

void servo_driver::steer_callback(const std_msgs::Float64::ConstPtr& steer_msg)
{
	steer = steer_msg->data;
	std::cout<<"Recieved Steer Command: "<<steer<<std::endl;
}

void servo_driver::publish2servo()
{
	servo_array_driver::ServoArray array_msg;
	servo_array_driver::Servo speed_servo;
	servo_array_driver::Servo steer_servo;

///////////////////////////////////////////////////////////////////////////////
//BUILD SERVO MESSAGES ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

	//steer servo msg
	if (steer>steer_range)
	{
		steer_servo.value = steer_0+steer_range;
	}
	else if (steer<0-steer_range)
	{
		steer_servo.value = steer_0-steer_range;
	}
	else
	{
		steer_servo.value = steer+steer_0;		
	}
	steer_servo.servo = 2;

	//speed servo msg
	if (speed>speed_range)
	{
		speed_servo.value = speed_0+speed_range;
	}
	else if (speed<0-speed_range)
	{
		speed_servo.value = speed_0-speed_range;
	}
	else
	{
		speed_servo.value = speed+speed_0;
	}
	speed_servo.servo = 1;
	
///////////////////////////////////////////////////////////////////////////////
//SEND SERVO MESSAGES /////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

	//build array msg
	array_msg.servos.push_back(speed_servo);
	array_msg.servos.push_back(steer_servo);

	//publish message
	servo_pub.publish(array_msg);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "server_array_driver_node");
	servo_driver ros_wrapper;
	ros::Rate loop_rate(50);

	while(ros::ok())
	{
		ros_wrapper.publish2servo();
		ros::spinOnce();
	}
	return 0;
}