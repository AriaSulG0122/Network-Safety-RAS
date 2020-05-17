#include <windows.h>
#include <stdio.h>
#include "CDesOperate.h"
#pragma comment(lib,"ws2_32.lib")


int runClient()
{
	//1.�����׽��ֿ�
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err) { printf("C: Failed to load socket library\n"); }
	else { printf("C: Success to load socket library\n"); }
	//2.����һ���׽��ֹ�ʹ��
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	//3.�������������������
	SOCKADDR_IN socksin;//��¼�������˵�ַ
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
		while (1) 
		{  //����������Ϣ
			printf("C: Please input the plaintext:");
			setbuf(stdin, NULL);
			scanf("%[^\n]s", plaintext);//ʹ�ÿ��д����ȡ��϶����ǿո�
			bool exit = false;
			if (strcmp(plaintext, "exit") == 0) { exit=true; }
			op.MakeData(plaintext);
			int count = 0;
			char time[64];
			strcpy(time,op.getTime());
			printf("C: [%s]Send the ciphtext to server:",time);
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
			send(ServerSocket, ciphtext, strlen(ciphtext), 0);
			if (exit) { break; }
			//���÷��ص��׽��ֺͷ�����ͨ�ţ����ռ�����Ϣ
			char s[256] = { 0 };
			recv(ServerSocket, s, 256, 0);
			printf("\nC: Receive server data:%s\n", s);
			memset(op.plaintext, 0, sizeof(op.plaintext));//��ʼ������
			//�յ�������Ϣ�󣬽��н���
			op.groupCount = 0;
			for (int i = 0; i < strlen(s); i++)//����յ��ļ�����Ϣ��תΪ����������
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
			//������ܺ������
			strcpy(time,op.getTime());
			printf("C: [%s]After decoding,get data:", time);
			for (int i = 0; i < op.groupCount; i++)
			{
				op.Bit2Char(op.textArray[i]);
			}
			printf("%s\n", op.plaintext);
			if (strcmp(op.plaintext, "exit") == 0) { break; }
		}
		//����û�ѡ���˳�����������������˳�����
		printf("\nC: Exit now...");
	}
	closesocket(ServerSocket);
	WSACleanup();
	return 0;
}