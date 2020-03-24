#include "iostream"
#include "CDesOperate.h"
using namespace std;

int main()
{
	char key[10] = {0},plaintext[255];
	printf("Please input the key:");
    scanf("%s", key);
	op.MakeKey(key);
	printf("\nPlease input the plaintext:");
	setbuf(stdin, NULL);
    scanf("%[^\n]s", plaintext);//使得空行代表读取完毕而不是空格
	op.MakeData(plaintext);
	for (int i = 0; i < op.groupCount; i++) 
	{
		op.MakeCiph(op.ciphArray[i], i);
	}
	return 1;
}