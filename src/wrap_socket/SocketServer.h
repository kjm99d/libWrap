#pragma once

#include <thread> // thread를 사용하기 위한 라이브러리

#pragma comment(lib, "ws2_32.lib")
#include <stdlib.h>
#include <WinSock2.h>
#include <queue>

#pragma hdrstop

using namespace std;

class SocketServer
{
public:
	SocketServer() {};
	~SocketServer() {};

	

	static SocketServer& GetInstance();
	void Init(const char * port = "9000");
	void Init(const int c_port);
	void Listen();
	bool Accept();
	void SendPtr(void* c, int size);
	//void Send(const char *c, int size);
	void Send2();
	void Recv();
	void Close();
	void Free();
	bool is_terminate();

	
	int GetCount() { return clients.size(); }

	queue<SOCKET> clients;


	void PrintMember() {
		printf("Par Clients = 0x%X \n", &clients);

	} ;

protected:
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr , clntAddr;
	int szClntAddr;

	bool Terminated;


	void ErrorHandling(const char* message);
	bool PortFilter(const int c_port);
};


class Management : public SocketServer
{
public:
	Management() { }
	static Management& GetInstance();
	void SendAll(std::string str);
	void SendUnique(int id, std::string str);
	void PrintMember();



	typedef struct {
		int id;
		SOCKET socket;
		
	} user;


	vector<user> u;

};
