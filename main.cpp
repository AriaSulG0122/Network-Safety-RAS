#include "iostream"
#include "CDesOperate.h"
#include "MyServer.h"
#include "MyClient.h"
using namespace std;

int main()
{	
	char mode[10] = { 0 };
	printf("Server or Client?Please Input S or C:");
	while (1) {
		scanf("%s", mode);
		if (mode[0] == 'S' || mode[0] == 's') { printf("I'm server.\n");runServer(); break; }
		else if (mode[0] == 'C' || mode[0] == 'c') { printf("I'm client\n"); runClient(); break; }
		else { printf("Wrong Input!!! Please input S or C:"); }
	}
	system("pause");
	return 1;
}