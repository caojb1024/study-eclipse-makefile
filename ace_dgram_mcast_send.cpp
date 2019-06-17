/*
 * ace_dgram_mcast_send.cpp
 *
 *  Created on: 2019年6月16日
 *      Author: bingcod
 */

#include <iostream>
#include <ace/SOCK_Dgram_Mcast.h>
#include <ace/Log_Msg.h>

int main() {

	ACE_INET_Addr mcast_addr(9999, "224.0.0.16");
	ACE_INET_Addr local_addr((u_short) 0);
	ACE_SOCK_Dgram sock(local_addr);

	char buf[512];
	while (true) {
		memset(buf, 0, sizeof(buf));
		std::cin.getline(buf, sizeof(buf));
		if (0 == strcmp("quit", buf)) {
			break;
		}
		if (sock.send(buf, sizeof(buf), mcast_addr) == -1) {
			ACE_ERROR((LM_ERROR,"send error"));
		}
	}
	return 0;
}
