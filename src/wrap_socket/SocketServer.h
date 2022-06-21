#pragma once

#include <thread> // thread를 사용하기 위한 라이브러리

#pragma comment(lib, "ws2_32.lib")
#include <stdlib.h>
#include <WinSock2.h>
#include <queue>
#include <mutex>
#pragma hdrstop

using namespace std;

class SocketServer
{
public:
	SocketServer() {};
	~SocketServer() {};

	mutex m;

	static SocketServer& GetInstance();
	void Init(const char * port);
	void Init(const int c_port);
	void Listen();
	void Accept();
	void Send(const char* msg);
	void Recv();
	void Close();
	void Free();
	bool is_terminate();

	
	int GetCount() { return clients.size(); }

private:
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr , clntAddr;
	int szClntAddr;

	queue<SOCKET> clients;

	bool Terminated;


	void ErrorHandling(const char* message);
	bool PortFilter(const int c_port);
};

