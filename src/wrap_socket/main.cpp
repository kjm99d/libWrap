#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#pragma hdrstop
using namespace std;

#define NAME "SOCKET SERVER"
#include "SocketServer.h"
#include <mutex>

void Listen();

mutex s;

void Listen()
{
	static int id = 0;
	Management& server = Management::GetInstance();
	server.Init();

	while (!server.is_terminate())
	{
		server.Listen();
		bool r = server.Accept();
		if (r == false) break;

		// True Then
		SOCKET& back = server.clients.back();
		server.u.push_back({ id, back });
		++id;
	}

	server.Close();
	server.Free();
	
}


void SendMsg()
{
	
	Management& server = Management::GetInstance();

	server.PrintMember();

	int seq = 0;
	while (!server.is_terminate()) 
	{
		static int n = 0;
		printf("U_IN : ");
		scanf("%d", &n);
		int cli_s = server.u.size();
		if (cli_s > n) 
		{
			char t[100] = { NULL, };
			printf("MSG : ");
			scanf("%s", t);
			string s = t;

			++seq;
			printf("Send \n");
			Sleep(1000);
			//string s = std::to_string(seq) + " GOGO ! \n";
			server.SendUnique(n, t);
		}

	}
}

#if 1

void Func() {

	Management& server = Management::GetInstance();

	while (!server.is_terminate())
	{
		server.Listen();
		server.Accept();

	}
}

int main(int argc, const char* argv[])
{
	cout << NAME << endl;
	Management::GetInstance();

	thread _t1(Listen);
	thread _t2(SendMsg);

	_t1.join();
	_t2.join();


	return 0;
}


#else

void ErrorHandling(const char* message);

int main(int argc, const char* argv[])
{
	cout << NAME << endl;

	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	const char* port;

	int szClntAddr;
	char message[] = "Hello World!";
	if (argc >= 2)
	{
		printf("Usage:%s< port > \n", argv[0]);
		printf("Set Default Port 9000 \n");
		//exit(1);
		port = argv[1];
	}
	else {
		port = "9000";
	}






	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //家南 扼捞宏矾府 檬扁拳
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_STREAM, 0); //家南积己

	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");



	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(port));



	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) //家南俊 IP林家客 PORT 锅龋 且寸
		ErrorHandling("bind() error");



	if (listen(hServSock, 5) == SOCKET_ERROR) //listen 窃荐龋免阑 烹秦辑 积己茄 家南阑 辑滚 家南栏肺 肯己
		ErrorHandling("listen() error");



	szClntAddr = sizeof(clntAddr);

	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr); //努扼捞攫飘 楷搬夸没 荐遏窍扁 困秦 accept窃荐 龋免

	if (hClntSock == INVALID_SOCKET)
		ErrorHandling("accept() error");

	send(hClntSock, message, sizeof(message), 0); //send窃荐 龋免阑 烹秦辑 楷搬等 努扼捞攫飘俊 单捞磐甫 傈价
	closesocket(hClntSock);

	closesocket(hServSock);
	WSACleanup();
	//橇肺弊伐 辆丰 傈俊 檬扁拳茄 家南 扼捞宏矾府 秦力

	return 0;
}

void ErrorHandling(const char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);

}

#endif