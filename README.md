# servo_array_driver
Package to interface with servo array on jet racer.

The servo array on the Jet Racer Cars uses a system of custom messages. This package simplifies this interface to be two std_msgs/Float64 messages on topics: "/vehicle/steering_cmd" and "/vehicle/speed_cmd"

This package has a config file (servo_array_driver/config/config.yaml) that allows the user to set the nuetral servo values as well as the range of acceptable servo input values.

/vehicle/steering_cmd (std_msgs/Float64): The value sent over this topic is the commanded steering left or right of the designated nominal value defined in the package config file. Positive values are to the right and negative is left. 

/vehicle/speed_cmd (std_msgs/Float64): The value sent over this topic is the command speed servo command. The package is set to recieve a positive value for a forward command and a negative for a backwards command. 
Note: The original custom messages expects this value to be negative for forward but the package accounts for this in it's callback.
