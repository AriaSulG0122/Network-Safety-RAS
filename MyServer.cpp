#include <windows.h>
#include <stdio.h>
#include "MyServer.h"
#pragma comment(lib,"ws2_32.lib")

int runServer()
{
	//1.加载套接字库
	WORD wVersionRequested=MAKEWORD(2,2);
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err) { printf("S: Failed to load socket library\n"); }
	else {printf("S: Success to load socket library\n");}
	//2.创建一个套接字供使用
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	//3.将套接字绑定到本地地址和端口上
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(6020);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	bind(ServerSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));
	//4.将套接字设置为监听模式，以接收客户端请求
	err = listen(ServerSocket, 5);
	if (err) { printf("S: Failed to listen\n"); }
	else { printf("S: Success to listen\n"); }
	//5.等待并接收客户端请求，返回新的连接套接字
	SOCKADDR_IN addr_out;
	int len = sizeof(SOCKADDR);
	SOCKET accSock = accept(ServerSocket, (SOCKADDR*)&addr_out, &len);
	//6.利用返回的套接字和客户端通信
	char s[256] = { 0 };
	recv(accSock, s, 256, 0);
	printf("S: Client Dada:%s \n", s);
	getchar();
	//7.关闭套接字
	closesocket(ServerSocket);
	WSACleanup();
	return 0;
}