#ifndef SERVO_ARRAY_DRIVER_NODE_H
#define SERVO_ARRAY_DRIVER_NODE_H

#include <ros/ros.h>
#include "std_msgs/Float64.h"
#include "servo_array_driver/ServoArray.h"
#include "servo_array_driver/Servo.h"

#include <iostream>
class servo_driver
{
	private:
	//ROS SETUP
	ros::NodeHandle n;
	ros::Publisher servo_pub;
	ros::Subscriber speed_sub;
	ros::Subscriber steer_sub;
	
	//CALLBACK FUNCTIONS
	void speed_callback(const std_msgs::Float64::ConstPtr&);
	void steer_callback(const std_msgs::Float64::ConstPtr&);
	
	double steer_0, steer, speed_0, speed, steer_range, speed_range;

	public:
	servo_driver();
	~servo_driver();
	void publish2servo();
};

#endif