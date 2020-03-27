#include <windows.h>
#include <stdio.h>
#include "MyServer.h"
#include "CDesOperate.h"
#pragma comment(lib,"ws2_32.lib")

int runServer()
{
	//1.加载套接字库
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err) { printf("S: Failed to load socket library\n"); }
	else { printf("S: Success to load socket library\n"); }
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
	//6.计算密钥	
		char key[10] = { 0 };
		printf("Please input the key:");
		scanf("%s", key);
		op.MakeKey(key);
	while (1)//当客户端没有退出时，服务器也不退出
	{
		memset(op.plaintext, 0, sizeof(op.plaintext));//初始化明文
		//利用返回的套接字和客户端通信，接收加密信息
		char s[256] = { 0 };
		recv(accSock, s, 256, 0);
		printf("S: Receive client data:%s\n", s);
		//收到加密信息后，进行解密
		op.groupCount = 0;
		for (int i = 0; i < strlen(s); i++)//拆解收到的加密信息，转为二进制数组
		{
			op.ciphArray[op.groupCount][i % 64] = s[i] - 48;
			if ((i + 1) % 64 == 0)
			{
				op.groupCount++;
			}
		}
		
		for (int i = 0; i < op.groupCount; i++)
		{
			op.MakeCiph(op.ciphArray[i], i);
		}
		//输出解密后的信息
		printf("S: After decoding,get data:");
		for (int i = 0; i < op.groupCount; i++)
		{
			op.Bit2Char(op.textArray[i]);
		}
		printf("%s\n", op.plaintext);
		if (op.plaintext == "QUIT") { printf("\nS: Exit the server!"); break; }
	}
	//关闭套接字
	closesocket(ServerSocket);
	WSACleanup();
	return 0;
}