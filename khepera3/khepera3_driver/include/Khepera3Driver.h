/*
 * K3Driver.h
 *
 *  Created on: Jun 8, 2011
 *      Author: jdelacroix
 */

#ifndef K3DRIVER_H_
#define K3DRIVER_H_

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket() and bind() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#include <errno.h>
#include <signal.h>

#include <math.h>

#include <ros/ros.h>

#include "khepera3_driver/UnicycleControl.h"
#include "khepera3_driver/SensorData.h"

class Khepera3Driver {

private:

	ros::NodeHandle m_node_handle;

	ros::ServiceServer m_data_receiver;
	ros::ServiceServer m_control_sender;

	std::string m_ip_address;
	int m_port;

	struct sigaction m_signal_callback;	/* Signal for timeouts */

	int m_socket;                        /* Socket */
	struct sockaddr_in m_server_address; 	/* Local address */
	struct sockaddr_in m_client_address; 	/* Client address */

	int m_timeout;

//	void m_alarm_callback(int arg);

	bool send_control(khepera3_driver::UnicycleControl::Request &req,
					  khepera3_driver::UnicycleControl::Response &res);

	bool receive_data(khepera3_driver::SensorData::Request &req,
				      khepera3_driver::SensorData::Response &res);

	bool receive_data_udp(char *reply);
	bool send_control_udp(int right_wheel_speed, int left_wheel_speed);



public:

	Khepera3Driver();
	virtual ~Khepera3Driver();
	void run();
	void connect();
	void disconnect();

};

#endif /* K3DRIVER_H_ */
