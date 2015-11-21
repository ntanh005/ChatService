#pragma once
#include "ChatSocket.h"
class TcpServerSocket : public ChatSocket
{
public:
	TcpServerSocket();
	TcpServerSocket(const char* address, int port);
	~TcpServerSocket();
	void run();
};

