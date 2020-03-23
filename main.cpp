#include "iostream"
#include "CDesOperate.h"
using namespace std;

int main()
{
	char key[10] = {0};
	printf("Please input the key:");
    scanf("%s", key);
	op.MakeKey(key);
	return 1;
}