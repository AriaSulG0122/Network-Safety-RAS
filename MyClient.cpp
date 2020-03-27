#include <windows.h>
#include <stdio.h>
#include "CDesOperate.h"
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
		printf("C: Success to connect to server\n");
		char key[10] = { 0 }, plaintext[255], ciphtext[500] = { 0 };
		printf("C: Please input the key:");
		scanf("%s", key);
		op.MakeKey(key);
		bool Continue = true;
		while (Continue) {//如果用户需要继续发送信息，则继续发送
			printf("C: Please input the plaintext:");
			setbuf(stdin, NULL);
			scanf("%[^\n]s", plaintext);//使得空行代表读取完毕而不是空格
			op.MakeData(plaintext);
			int count = 0;
			printf("\nC: Send the ciphtext to server:");
			for (int i = 0; i < op.groupCount; i++)
			{
				for (int j = 0; j < 64; j++)
				{
					ciphtext[count++] = op.ciphArray[i][j] + 48;//***这里注意，要加上48
				}
			}
			ciphtext[count] = '\0';
			printf("%s ", ciphtext);
			//发送数据给服务器
			send(ServerSocket, ciphtext, strlen(ciphtext), 0);
			//用户选择是否继续通讯
			printf("\nC: If continue to send message?(Y/N)");
			char command[10] = { 0 };
			while (1) {
				scanf("%s", command);
				if (command[0] == 'Y' || command[0] == 'y') { break; }
				else if (command[0] == 'N' || command[0] == 'n') { printf("\nExit!"); Continue = false; break; }
				else { printf("Wrong Input!!! Please input Y or N:"); }
			}
		}
		//如果用户选择退出，则向服务器发送退出请求
		char exit[] = "0100111000011110011000010010000010010111000110001011100110101011";
		send(ServerSocket, exit, strlen(exit), 0);
	}
	closesocket(ServerSocket);
	WSACleanup();
	return 0;
}