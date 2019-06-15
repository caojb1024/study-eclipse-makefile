/*
 * ace_mul_echo_server.cpp
 *
 *  Created on: 2019年6月15日
 *      Author: bingcod
 */

#include <ace/INET_Addr.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Thread_Manager.h>
#include <ace/Log_Msg.h>

static ACE_THR_FUNC_RETURN handler(void* arg) {
	ACE_SOCK_Stream* peer = static_cast<ACE_SOCK_Stream*>(arg);
	char buf[512];
	ssize_t n = 0;
	while (true) {
		memset(buf, 0, sizeof(buf));
		if ((n = peer->recv(buf, sizeof(buf))) == -1) {
			ACE_ERROR((LM_ERROR,"%p\n","recv() error."));
			break;
		}
		if (peer->send(buf, n) == -1) {
			ACE_ERROR((LM_ERROR,"%p\n","send() error."));
		}
	}
	peer->close();
	delete peer;
	return 0;
}

int main() {

	ACE_INET_Addr srv_addr;
	ACE_SOCK_Acceptor acceptor;

	if (srv_addr.set(8888) == -1) {
		ACE_ERROR_RETURN((LM_ERROR, "%p\n", "set() error."), 1);
	}
	if (acceptor.open(srv_addr, 1) == -1) {
		ACE_ERROR_RETURN((LM_ERROR, "%p\n", "open() error."), 1);
	}

	while (true) {
		ACE_SOCK_Stream* peer = new ACE_SOCK_Stream;
		if (acceptor.accept(*peer) == -1) {
			ACE_ERROR_RETURN((LM_ERROR, "%p\n", "accept() error."), 1);
		} else {
			peer->disable(ACE_NONBLOCK);
			ACE_Thread_Manager::instance()->spawn(handler, peer,
			THR_SCOPE_PROCESS | THR_NEW_LWP | THR_DETACHED);
		}
	}
	return acceptor.close() == -1 ? 1 : 0;
}

