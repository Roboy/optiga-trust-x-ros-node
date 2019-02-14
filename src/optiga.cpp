#include "ros/ros.h"
#include "std_srvs/Empty.h"
#include <iostream>

extern "C" {
	int32_t sign();
}

bool sign_srv(std_srvs::Empty::Request &req,
		std_srvs::Empty::Response &res) {
	sign();
	return true;
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "optiga_node");
	ros::NodeHandle nh;
	
	ros::ServiceServer service = nh.advertiseService("optiga", sign_srv);
	ros::spin();

	return 0;
}
