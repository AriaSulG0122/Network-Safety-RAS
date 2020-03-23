#include "CDesOperate.h"
#include "StaticArray.h"
#include "stdio.h"
static bool Debug = true;
INT32 CDesOperate::MakeKey(char *key)
{
	short tmp[64] = { 0 };
	//将key放入到数组
	for (int i = 0; i < 8; i++)
	{
		//printf("\n%d:", key[i]);
		for (int j = 0; j < 7; j++)
		{
			tmp[i * 8 + 7 - j-1] = key[i] % 2;
			key[i] = key[i] / 2;
		}
		//设置奇偶校验位
		int count = 0;
		for (int j = 0; j < 7; j++) {
			if (tmp[i * 8 + j]) { count++; }
			//printf("%d ", tmp[i * 8 + j]);
		}
		if (!(count % 2)) { tmp[i * 8 + 7] = 1; }
		//printf("%d ", tmp[i*8+7]);
	}
	//printf("\n");
	short Ikey[56];
	//对key进行初始置换，得到IP(K)
	for (int i = 0; i < 56; i++)
	{
		Ikey[i] = tmp[keyarray[i]-1];
		if(Debug){printf("%d ", Ikey[i]);
		if((i+1)%14==0)printf("\n");}
	}
	//进行移位
	UINT64 tempKey=0;
	for (int i = 0; i < 16; i++)
	{
		short tmpK[56];
		if (i == 0 || i == 1 || i == 15)//左移1位
		{
			tmpK[27] = Ikey[0];
			for (int j = 0; j < 27; j++)
			{
				tmpK[j] = Ikey[j+1];
				//if(Debug)printf("%d ", tmpK[j]);
			}
			//if(Debug)printf("%d \n", tmpK[27]);
			tmpK[55] = Ikey[28];
			for (int j = 28; j < 55; j++)
			{
				tmpK[j] = Ikey[j+1];
				//if(Debug)printf("%d ", tmpK[j]);
			}
			//if(Debug)printf("%d \n", tmpK[55]);
		}
		else //左移2位
		{
			tmpK[26] = Ikey[0];
			tmpK[27] = Ikey[1];
			for (int j = 0; j < 26; j++)
			{
				tmpK[j] = Ikey[j+2];
			}
			tmpK[54] = Ikey[28];
			tmpK[55] = Ikey[29];
			for (int j = 28; j < 54; j++)
			{
				tmpK[j] = Ikey[j+2];
			}
		}
		//递归传给i+1
		for (int j = 0; j < 56; j++) { Ikey[j] = tmpK[j]; }
		//进行Pk选择，形成48位密钥
		if(Debug)printf("\ni=%d: ", i);
		for (int j = 0; j < 48; j++)
		{
			m_arrOutKey[i][j] = tmpK[keychoose[j]-1];
			if(Debug)printf("%d ", m_arrOutKey[i][j]);
		}
	}
	return 1;
}
/*INT32 CDesOperate::MakeData(char *plaintext)
{
	
	
	return 1;
}*/