#include <ace/SOCK_Dgram.h>
#include <ace/INET_Addr.h>
#include <ace/Log_Msg.h>
#include <iostream>

int main() {

	ACE_INET_Addr server_addr(8888, "localhost");
	ACE_INET_Addr local_addr;
	ACE_SOCK_Dgram peer(local_addr);

	char buf[512];
	while (true) {
		memset(buf, 0, sizeof(buf));
		std::cin.getline(buf, sizeof(buf));
		if (0 == strcmp("quit", buf)) {
			break;
		}
		ssize_t len = peer.send(buf, sizeof(buf), server_addr);
		memset(buf, 0, sizeof(buf));
		len = peer.recv(buf, sizeof(buf), local_addr);
		if (len > 0) {
			ACE_DEBUG((LM_DEBUG,"recv_from server[%s:%d]=>said[%s] \n",server_addr.get_host_addr(),server_addr.get_port_number(),buf));
		}
	}
	return 0;
}
