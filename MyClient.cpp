#include <windows.h>
#include <stdio.h>

#pragma comment(lib,"ws2_32.lib")

int runClient()
{
	//1.加载套接字库
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err) { printf("C: Failed to load socket library\n"); }
	else { printf("C: Success to load socket library\n"); }
	//2.创建一个套接字供使用
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	//3.向服务器发出连接请求
	SOCKADDR_IN socksin;//记录服务器端地址
	socksin.sin_family = AF_INET;
	socksin.sin_port = htons(6020);
	socksin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int rf = connect(ServerSocket, (SOCKADDR*)&socksin, sizeof(socksin));
	if (rf == SOCKET_ERROR)
	{
		printf("C: Failed to connect to server\n");
	}
	else
	{
		printf("C: Success to connect to server\nC: Please input the plaintext:");
		char plaintext[100];
		scanf("%s", plaintext);
		send(ServerSocket, plaintext, strlen(plaintext), 0);
	}
	getchar();
	closesocket(ServerSocket);
	WSACleanup();
	return 0;
}