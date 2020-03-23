#pragma once
#include "windows.h"
typedef int INT32;

class CDesOperate
{
public:
	short m_arrOutKey[16][48];//16轮迭代密钥
	ULONG32 m_arrBufKey[2];
	INT32 HandleData(ULONG32 *left, short choice);//执行一次完整的加密或解密操作
	INT32 MakeData(ULONG32 *left, ULONG32 *right);//实现16轮加密或解密迭代中的每一轮，除去初始置换和逆初始置换
	INT32 MakeKey(char *key);//形成16个密钥中的每一个子密钥，记录到对应数组中
public:
	//CDesOperate();//构造函数
	//~CDesOperate();//析构函数
	INT32 Encry(char* pPlaintext, int nPlaintextLength, char *pCipherBuffer,
		int &nCipherBufferLength, char *pKey, int nKeyLength);//对某一段字符加密
	INT32 Decry(char* pCipher, int nCipherBufferLength, char *pPlaintextBuffer,
		int &nPlaintextBufferLength, char *pKey, int nKeyLength);//对某一段密文解密
};
static CDesOperate op;