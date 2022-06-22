#include <iostream>
#include <mutex>
#pragma hdrstop

#include "SocketServer.h"

std::mutex singleton;

void SocketServer::Listen()
{
	if (listen(hServSock, 5) == SOCKET_ERROR) //listen 함수호출을 통해서 생성한 소켓을 서버 소켓으로 완성
		ErrorHandling("listen() error");
}

bool SocketServer::Accept()
{
	szClntAddr = sizeof(clntAddr);

	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr); //클라이언트 연결요청 수락하기 위해 accept함수 호출

	if (hClntSock == INVALID_SOCKET) return false;
		//ErrorHandling("accept() error");

	clients.push(hClntSock);
	printf("clients = 0x%X \n", &clients);


	return true;
}

void SocketServer::SendPtr(void* c, int size)
{
	int i;
	printf("clients = 0x%X \n", &clients);
	int len_clients = clients.size();
	for (i = 0; i < len_clients; ++i) {
		SOCKET& client = clients.front();
		clients.pop();
		send(client, (const char *)c, sizeof(unsigned char) * size, 0); //send함수 호출을 통해서 연결된 클라이언트에 데이터를 전송
		clients.push(client);
		
	}
}
#if 0
void SocketServer::Send(const char* c, int size)
{
	int i;
	int len_clients = clients.size();
	for (i = 0; i < len_clients; ++i) {
		SOCKET& client = clients.front();
		clients.pop();
		send(client, c, sizeof(char) * size, 0); //send함수 호출을 통해서 연결된 클라이언트에 데이터를 전송
		clients.push(client);

	}
}
#endif
void SocketServer::Send2()
{
}

void SocketServer::Recv()
{
}

void SocketServer::Close()
{
	printf("Close \n");
	int len_clients = clients.size();
	while (clients.size()) {
		SOCKET& client = clients.front();
		clients.pop();
		closesocket(client);
	}

}

void SocketServer::Free()
{
	Terminated = true;
	printf("Free Start \n");

	closesocket(hServSock);
	WSACleanup();
	printf("Free End \n");
}

bool SocketServer::is_terminate()
{
	return Terminated;
}

void SocketServer::ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

bool SocketServer::PortFilter(const int c_port)
{
	bool ret = true;
	
	switch (c_port)
	{
	case 0:
	case 21:
	case 80:
		ret = false;
	}

	return ret;
}

SocketServer& SocketServer::GetInstance()
{
	static SocketServer* server = NULL;
	if (server == NULL) {
		server = new SocketServer();
	}

	return (*server);
	// // O: 여기에 return 문을 삽입합니다.
}

void SocketServer::Init(const char* port)
{
	int port_i = atoi(port);
	Init(port_i);
}

void SocketServer::Init(const int c_port)
{
	int port = c_port;

	// 포트 필터링
	if (port == 0 || port < 1) {
		port = 9000;
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //소켓 라이브러리 초기화
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_STREAM, 0); //소켓생성

	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) //소켓에 IP주소와 PORT 번호 할당
	{
		ErrorHandling("bind() error");
	}
}

Management& Management::GetInstance()
{

	static Management* server = NULL;
	if (server == NULL) {
		server = new Management();
	}
	return (*server);
}

void Management::SendAll(std::string str)
{
	//unsigned char t[] = { 65,65, '\n' };
	//Send(str.c_str(), str.size());
	SendPtr((void *)str.c_str(), str.size());

}

void Management::SendUnique(int id, std::string str)
{
	const SOCKET client = u.at(id).socket;		
	send(client, str.c_str(), sizeof(const char) * str.size(), 0); //send함수 호출을 통해서 연결된 클라이언트에 데이터를 전송

}

void Management::PrintMember()
{
	SocketServer::PrintMember();
	printf("Chi Clients = 0x%X \n", &clients);
}
