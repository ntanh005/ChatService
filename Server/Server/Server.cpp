// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <LogLib.h>
#include "define.h"
#include "TcpServerSocket.h"
int main()
{
	GetLOG()->Log("SERVER start");

	TcpServerSocket* sever = new TcpServerSocket(SERVER_ADDRESS,  SERVER_PORT);
	sever->run();
	GetLOG()->Log("SERVER end");
    return 0;
}

