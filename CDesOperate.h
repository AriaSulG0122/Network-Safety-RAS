
#pragma once
#include "windows.h"
typedef int INT32;

class CDesOperate
{
public:
	short groupCount;
	short keyArray[16][48];//16轮迭代密钥
	short textArray[17][64];//明文数组
	short ciphArray[17][64];//密文数组
	char plaintext[255];//记录解密后的明文字符串
	INT32 MakeData(char *plaintext);//实现16轮加密或解密迭代中的每一轮，除去初始置换和逆初始置换
	INT32 MakeCiph(short *ciphtext,int k);
	INT32 MakeKey(char *key);//形成16个密钥中的每一个子密钥，记录到对应数组中
	int Bit2Char(short *BitArray);
public:
	//CDesOperate();//构造函数
	//~CDesOperate();//析构函数
	int encry(int k);
	int decry(int k);
};
extern CDesOperate op;