#include "ros/ros.h"
#include "std_srvs/Empty.h"
#include "roboy_middleware_msgs/OptigaSign.h"
#include <iostream>

#define OPTIGA_LIB_SUCCESS             0x0000
#define OPTIGA_LIB_ERROR               0xFFFF

extern "C" {
	int32_t sign(uint8_t * digest, uint8_t digest_length,
			uint8_t * signature, uint16_t * signature_length);
	int32_t init_optiga();
	int32_t asn1_to_ecdsa_rs(const uint8_t * asn1, size_t asn1_len,
										 uint8_t * rs, size_t * rs_len);
}

bool sign_srv(roboy_middleware_msgs::OptigaSign::Request &req,
		roboy_middleware_msgs::OptigaSign::Response &res) {

	uint8_t signature[70];

	uint8_t digest_length = req.digest.size();

	uint16_t signature_length = sizeof(signature);
	
	int32_t status = sign(&req.digest[0], digest_length, 
		signature, &signature_length);

	if (status == OPTIGA_LIB_SUCCESS) {

		for (int i = 0; i<signature_length; i++) {
			res.signature.push_back(signature[i]);
		}
		return true;
	}


	return false;
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "optiga_signee");
	ros::NodeHandle nh;

	ros::ServiceServer service = nh.advertiseService("optiga", sign_srv);
	if (init_optiga() == OPTIGA_LIB_ERROR)
		return -1;
	
	ros::spin();

	return 0;
}
