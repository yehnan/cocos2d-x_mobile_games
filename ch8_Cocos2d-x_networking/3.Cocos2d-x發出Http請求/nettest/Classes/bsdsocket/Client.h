#pragma once

#include <iostream>
#include "ODSocket.h"


class Client
{
public:
	Client();
	~Client();
	void  init();
	void  sendMessage(char *);
	void  recvMessage();
protected:
	ODSocket		m_odSocket;
};