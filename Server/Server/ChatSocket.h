#pragma once
#include <LogLib.h>
class ChatSocket
{
public:
	ChatSocket();
	~ChatSocket();
	virtual void run() = 0;
};

