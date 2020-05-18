#include "iostream"
#include "CDesOperate.h"
#include "MyServer.h"
#include "MyClient.h"
#include "StaticArray.h"
#include "CRSAOperate.h"
using namespace std;

int main()
{	
	//printf("%d\n", &pc_first);
	char mode[10] = { 0 };
	printf("Server or Client?Please Input S or C:");

	//op.MakeKey("BLACKHAT");
	/*测试Euclid函数是否正确实现
	UINT64 d = Euclid(7, 160);
	printf("d:%d\n", d);
	*/
	
	/*while (1) {
		scanf("%s", mode);
		if (mode[0] == 'S' || mode[0] == 's') { printf("I'm server.\n");runServer(); break; }
		else if (mode[0] == 'C' || mode[0] == 'c') { printf("I'm client\n"); runClient(); break; }
		else { printf("Wrong Input!!! Please input S or C:"); }
	}*/

	system("pause");
	return 1;
}