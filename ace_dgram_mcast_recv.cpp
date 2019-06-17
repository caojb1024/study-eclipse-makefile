/*
 * ace_dgram_mcast_recv.cpp
 *
 *  Created on: 2019年6月17日
 *      Author: bingcod
 */
#include <ace/SOCK_Dgram_Mcast.h>
#include <ace/Log_Msg.h>

int main() {

	ACE_INET_Addr mcast_addr(9999, "224.0.0.16");
	ACE_INET_Addr remote_addr((u_short) 0);
	ACE_SOCK_Dgram_Mcast sock;

	if (sock.join(mcast_addr) == -1) {
		ACE_ERROR((LM_ERROR,"%p\n","join error."));
	}
	char buf[512];
	while (true) {
		ACE_DEBUG((LM_DEBUG,"while open-0.\n"));
		memset(buf, 0, sizeof(buf));
		ACE_DEBUG((LM_DEBUG,"while open-1.\n"));
		if (sock.recv(buf, sizeof(buf), remote_addr) != -1) {
			ACE_DEBUG(
					(LM_DEBUG,"recv msg from [%s:%d]:%s \n",remote_addr.get_host_addr(), remote_addr.get_port_number(),buf));
		}else{
			ACE_ERROR((LM_ERROR,"%p\n","recv error."));
		}
	}
	if (sock.leave(mcast_addr) == -1) {
		ACE_ERROR((LM_ERROR,"%p\n","leave error."));
	}
	return 1;
}

