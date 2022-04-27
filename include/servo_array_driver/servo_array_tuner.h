#include <ros/ros.h>
#include <i2cpwm_board/Servo.h>
#include <i2cpwm_board/ServoArray.h>

#include <dynamic_reconfigure/server.h>
#include <servo_array_driver/ServoTuneConfig.h>

class servo_array_tuner
{
    private:
    ros::NodeHandle n;
    ros::Publisher servo_pub;

    double steer;
    double speed;
    bool flag;

    void ReconfigureCallback(const servo_array_driver::ServoTuneConfig &config, uint32_t level);

    std::shared_ptr<ros::NodeHandle> nodePtr_;
    std::shared_ptr<dynamic_reconfigure::Server<servo_array_driver::ServoTuneConfig>> reconfigServerPtr_;

    public:
    void publish_servo();
    servo_array_tuner();
    ~servo_array_tuner();    
};

