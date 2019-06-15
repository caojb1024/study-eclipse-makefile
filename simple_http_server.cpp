/*
 * simple_http_server.cpp
 *
 *  Created on: 2019年6月14日
 *      Author: bingcod
 */

#include <ace/INET_Addr.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Connector.h>
#include <ace/Log_Msg.h>
#include <ace/Mem_Map.h>

#include <iostream>
using namespace std;

extern char* get_url_pathname(ACE_SOCK_Stream* peer);

int main()
{

	ACE_INET_Addr server_addr;
	ACE_SOCK_Acceptor acceptor;
	ACE_SOCK_Stream peer;

	if (server_addr.set(8888) == -1)
	{
		ACE_ERROR_RETURN((LM_ERROR,"%p\n","server_addr.set(8888) error."), 1);
	}
	cout << "server_addr.set(8888) success." << endl;
	if (acceptor.open(server_addr) == -1)
	{
		ACE_ERROR_RETURN((LM_ERROR,"%p\n","acceptor.open(server_addr) error."),
				1);
	}
	cout << "acceptor.open(server_addr) success." << endl;
	while (true)
	{
		cout << "while-start." << endl;
		if (acceptor.accept(peer) == -1)
		{
			ACE_ERROR_RETURN((LM_ERROR,"%p\n","accept(peer) error."), 1);
		}
		peer.disable(ACE_NONBLOCK);
		char* pathname = get_url_pathname(&peer);

		ACE_Mem_Map mapped_file(pathname);
		delete[] pathname;

		if (peer.send_n(mapped_file.addr(), mapped_file.size()) == -1)
		{
			ACE_ERROR_RETURN((LM_ERROR,"%p\n","send_n() error."), 1);
		}
		cout << "return success." << endl;
		peer.close();
		cout << "while-end." << endl;
	}
	return acceptor.close() == -1 ? 1 : 0;
}

char* get_url_pathname(ACE_SOCK_Stream* peer)
{
	static const char* docBase = "./web";
	char buff[512];
	if (peer->recv(buff, sizeof(buff)) != -1)
	{
		// "GET /index.html HTTP/1.0\r\n"
		const char* pos1 = strchr(buff, ' ');  // 可以查找字符串s中首次出现字符c的位置
		const char* pos2 = strchr(++pos1, ' ');
		const size_t len = pos2 - pos1;
		const size_t docLen = strlen(docBase); // 返回s的长度，不包括结束符NULL

		char* path = new char[len + docLen + 1];
		memcpy(path, docBase, docLen); // memcpy函数的功能是从源内存地址的起始位置开始拷贝若干个字节到目标内存地址中
		cout << "path1=" << path << endl;
		cout << "docLen=" << docLen << endl;
		memcpy(path + docLen, pos1, len);
		path[len + docLen] = '\0';
		cout << "path=" << path << endl;
		return path;
	}
	ACE_ERROR_RETURN((LM_ERROR,"%p\n","peer->recv error."), 0);
}

