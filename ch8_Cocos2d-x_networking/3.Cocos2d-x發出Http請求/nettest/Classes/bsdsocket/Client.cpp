#include "Client.h"

using namespace std;
const string SERVER_IP = "127.0.0.1";
const int	 SERVER_PORT = 9999;
Client::Client()
{

}

Client::~Client()
{

}

void Client::init()
{
	m_odSocket.Init();
	m_odSocket.Create(AF_INET,SOCK_STREAM,0);
	m_odSocket.Connect(SERVER_IP,SERVER_PORT);
}

void Client::recvMessage()
{
	char  buf[256];
	m_odSocket.Recv(buf,256);
	cout<<"recv the message :"<<buf<<endl;
}

void Client::sendMessage(char * msg)
{
	int len = strlen(msg)+1;
	m_odSocket.Send(msg,len);
}