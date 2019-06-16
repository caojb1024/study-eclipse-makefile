/**
 * ace_sap_dgram_echoserver.cpp
 */

#include <ace/SOCK_Dgram.h>
#include <ace/INET_Addr.h>
#include <ace/Log_Msg.h>

int main() {

	ACE_INET_Addr server_addr;
	if (server_addr.set(8888) == -1) {
		ACE_DEBUG((LM_DEBUG,"%p\n","set() error."));
	}
	ACE_SOCK_Dgram peer(server_addr);
	char buf[512];
	while (true) {
		memset(buf, 0, sizeof(buf));
		ACE_INET_Addr client_addr;
		ssize_t len = peer.recv(buf, sizeof(buf), client_addr);
		if (len > 0) {
			peer.send(buf, len, client_addr);
			ACE_DEBUG(
					(LM_DEBUG,"recv from[%s:%d]=>said[%s]\n",client_addr.get_host_addr(),client_addr.get_port_number(),buf));
		}
	}
	return 0;
}

