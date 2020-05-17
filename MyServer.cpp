#include <windows.h>
#include <stdio.h>
#include "MyServer.h"
#include "CDesOperate.h"
#pragma comment(lib,"ws2_32.lib")

int runServer()
{
	//1.�����׽��ֿ�
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err) { printf("S: Failed to load socket library\n"); }
	else { printf("S: Success to load socket library\n"); }
	//2.����һ���׽��ֹ�ʹ��
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	//3.���׽��ְ󶨵����ص�ַ�Ͷ˿���
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(6020);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	bind(ServerSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));
	//4.���׽�������Ϊ����ģʽ���Խ��տͻ�������
	err = listen(ServerSocket, 5);
	if (err) { printf("S: Failed to listen\n"); }
	else { printf("S: Success to listen\n"); }
	//5.�ȴ������տͻ������󣬷����µ������׽���
	SOCKADDR_IN addr_out;
	int len = sizeof(SOCKADDR);
	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&addr_out, &len);
	//6.������Կ	
	char key[10] = { 0 };
	printf("Please input the key:");
	scanf("%s", key);
	op.MakeKey(key);
	while (1)
	{
		memset(op.plaintext, 0, sizeof(op.plaintext));//��ʼ������
		//���÷��ص��׽��ֺͿͻ���ͨ��
		char s[256] = { 0 };
		recv(ClientSocket, s, 256, 0);//��������
		printf("\nS: Receive client data:%s\n", s);
		//����յ��ļ�����Ϣ��תΪ����������
		op.groupCount = 0;
		for (int i = 0; i < strlen(s); i++)
		{
			op.ciphArray[op.groupCount][i % 64] = s[i] - 48;
			if ((i + 1) % 64 == 0) { op.groupCount++; }
		}
		//�������ĵĽ���
		for (int i = 0; i < op.groupCount; i++)
		{
			op.MakeCiph(op.ciphArray[i], i);
		}
		//������ܺ������
		char time[64];
		strcpy(time,op.getTime());
		printf("S: [%s]After decoding,get data:", time);
		for (int i = 0; i < op.groupCount; i++)
		{
			op.Bit2Char(op.textArray[i]);
		}
		printf("%s\n", op.plaintext);
		if (strcmp(op.plaintext, "exit") == 0) { break; }


		//����û���Ҫ����������Ϣ�����������
		char plaintext[255] = { 0 }, ciphtext[500] = { 0 };
		printf("S: Please input the plaintext:");
		setbuf(stdin, NULL);
		scanf("%[^\n]s", plaintext);//ʹ�ÿ��д����ȡ��϶����ǿո�
		bool exit = false;
		if (strcmp(plaintext, "exit") == 0) { exit = true; }
		op.MakeData(plaintext);
		int count = 0;
		strcpy(time,op.getTime());
		printf("S: [%s]Send the ciphtext to client:",time);
		for (int i = 0; i < op.groupCount; i++)
		{
			for (int j = 0; j < 64; j++)
			{
				ciphtext[count++] = op.ciphArray[i][j] + 48;//***����ע�⣬Ҫ����48
			}
		}
		ciphtext[count] = '\0';
		printf("%s ", ciphtext);
		//�������ݸ�������
		send(ClientSocket, ciphtext, strlen(ciphtext), 0);
		if (exit) { break; }
	}
	printf("\nS: Exit now...");

	//�ر��׽���
	closesocket(ServerSocket);
	WSACleanup();
	return 0;
}