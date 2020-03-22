#pragma once
#include "WinDef.h"
typedef int INT32;
class CDesOperate
{
private:
	ULONG32 m_arrOutKey[16][2];//16轮迭代密钥
	ULONG32 m_arrBufKey[2];
	INT32 HandleData(ULONG32 *left, short choice);//执行一次完整的加密或解密操作
	INT32 MakeData(ULONG32 *left, ULONG32 *right, ULONG32 number);//实现16轮加密或解密迭代中的每一轮，除去初始置换和逆初始置换
	INT32 MakeKey(ULONG32 *keyleft, ULONG32 *keyright, ULONG32 number);//形成16个密钥中的每一个子密钥
	INT32 MakeFirstKey(ULONG32 *keyP);//利用用户输入的初始密钥，来形成16个迭代用到的子密钥
public:
	CDesOperate();//构造函数
	~CDesOperate();//析构函数
	INT32 Encry(char* pPlaintext, int nPlaintextLength, char *pCipherBuffer,
		int &nCipherBufferLength, char *pKey, int nKeyLength);//对某一段字符加密
	INT32 Decry(char* pCipher, int nCipherBufferLength, char *pPlaintextBuffer,
		int &nPlaintextBufferLength, char *pKey, int nKeyLength);//对某一段密文解密
};
