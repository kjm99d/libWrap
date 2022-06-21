#include <iostream>
#pragma hdrstop
#include "SocketServer.h"

void SocketServer::Listen()
{
	if (listen(hServSock, 5) == SOCKET_ERROR) //listen �Լ�ȣ���� ���ؼ� ������ ������ ���� �������� �ϼ�
		ErrorHandling("listen() error");
}

void SocketServer::Accept()
{

	szClntAddr = sizeof(clntAddr);

	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr); //Ŭ���̾�Ʈ �����û �����ϱ� ���� accept�Լ� ȣ��

	if (hClntSock == INVALID_SOCKET)
		ErrorHandling("accept() error");

	clients.push(hClntSock);

}

void SocketServer::Send(const char* msg)
{
	int i;
	int len_clients = clients.size();
	for (i = 0; i < len_clients; ++i) {
		SOCKET& client = clients.front();
		clients.pop();
		send(client, msg, sizeof(msg), 0); //send�Լ� ȣ���� ���ؼ� ����� Ŭ���̾�Ʈ�� �����͸� ����
		clients.push(client);
		
	}
}

void SocketServer::Recv()
{
}

void SocketServer::Close()
{
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
	m.lock();

	closesocket(hServSock);
	WSACleanup();
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
	// // O: ���⿡ return ���� �����մϴ�.
}

void SocketServer::Init(const char* port)
{
	int port_i = atoi(port);
	Init(port_i);
}

void SocketServer::Init(const int c_port)
{
	int port = c_port;

	// ��Ʈ ���͸�
	if (port == 0 || port < 1) {
		port = 9000;
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //���� ���̺귯�� �ʱ�ȭ
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_STREAM, 0); //���ϻ���

	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) //���Ͽ� IP�ּҿ� PORT ��ȣ �Ҵ�
	{
		ErrorHandling("bind() error");
	}
}
