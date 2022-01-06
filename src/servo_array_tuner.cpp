#include <servo_array_driver/servo_array_tuner.h>

servo_array_tuner::servo_array_tuner()
{
    servo_pub = n.advertise<servo_array_driver::ServoArray>("/servos_absolute", 1);

    this->nodePtr_.reset(new ros::NodeHandle("servo_array_tuner"));
    this->reconfigServerPtr_.reset(new dynamic_reconfigure::Server<servo_array_driver::ServoTuneConfig>(*this->nodePtr_));
    this->reconfigServerPtr_->setCallback(boost::bind(&servo_array_tuner::ReconfigureCallback, this, _1, _2));

    flag = false;
}

servo_array_tuner::~servo_array_tuner()
{
    // do nothing
}

void servo_array_tuner::ReconfigureCallback(const servo_array_driver::ServoTuneConfig &config, uint32_t level)
{
    speed = config.speed;
    steer = config.steer;
    flag = config.run;
    publish_servo();
}

void servo_array_tuner::publish_servo()
{
    servo_array_driver::ServoArray array_msg;
    servo_array_driver::Servo speed_msg;
    servo_array_driver::Servo steer_msg;

    speed_msg.servo = 1;
    speed_msg.value = speed;

    steer_msg.servo = 2;
    steer_msg.value = steer;

    array_msg.servos.push_back(speed_msg);
    array_msg.servos.push_back(steer_msg);

    if(flag)
    {
        servo_pub.publish(array_msg);
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "servo_tuner");
    servo_array_tuner tuner;
    ros::spin();
}