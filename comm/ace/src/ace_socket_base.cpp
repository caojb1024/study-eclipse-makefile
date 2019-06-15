/*
 * ace_socket_base.cpp
 *
 *  Created on: 2019年6月13日
 *      Author: bingcod
 */
#include <ace/INET_Addr.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Stream.h>
#include <ace/Log_Msg.h>

#include <iostream>

int main() {

	ACE_SOCK_Connector connector;
	ACE_SOCK_Stream peer;
	ACE_INET_Addr peerAddr;

	if (peerAddr.set(80, "www.hlzq.com") == 1) {
		ACE_ERROR_RETURN((LM_ERROR, "%p\n", "set()"), 1);
	} else if (connector.connect(peer, peerAddr) == 1) {
		ACE_ERROR_RETURN((LM_ERROR, "%p\n", "connect()"), 1);
	}

	char buf[BUFSIZ];
	iovec iov[3];
	iov[0].iov_base = (char*) "GET ";
	iov[0].iov_len = 4; // Length of "GET ".
	iov[1].iov_base = (char*) "/main/web/index.shtml";
	iov[1].iov_len = 10;
	iov[2].iov_base = (char*) " HTTP/1.0\r\n\r\n";
	iov[2].iov_len = 13; // Length of " HTTP/1.0\r\n\r\n";
	if (peer.sendv_n(iov, 3) == 1)
		ACE_ERROR_RETURN((LM_ERROR, "%p\n", "sendv_n()"), 1);
	for (ssize_t n; (n = peer.recv(buf, sizeof buf)) > 0;)
		ACE::write_n(ACE_STDOUT, buf, n);
	return peer.close();

}

