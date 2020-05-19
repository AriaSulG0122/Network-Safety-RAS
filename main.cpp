#include "iostream"
#include "CDesOperate.h"
#include "MyServer.h"
#include "MyClient.h"
#include "StaticArray.h"
#include "CRSAOperate.h"
using namespace std;
extern Paraments m_cParament;
int main()
{	
	//printf("%d\n", &pc_first);
	char mode[10] = { 0 };
	printf("Server or Client?Please Input S or C:");
	//随机产生DES密钥
	/*
	char randomKey[8];
	GenerateDesKey(randomKey);
	for (int i = 0; i < 8; i++) {
		cout << randomKey[i] << endl;
	}*/
	
	//op.MakeKey("BLACKHAT");
	//进行DES子钥生成
	//op.MakeKey(randomKey);
	

	while (1) {
		scanf("%s", mode);
		if (mode[0] == 'S' || mode[0] == 's') { printf("I'm server.\n");runServer(); break; }
		else if (mode[0] == 'C' || mode[0] == 'c') { printf("I'm client\n"); runClient(); break; }
		else { printf("Wrong Input!!! Please input S or C:"); }
	}


	/*测试Euclid函数是否正确实现
	UINT64 d = Euclid(7, 160);
	printf("d:%d\n", d);
	*/

	//测试能否顺利产生RSA参数，并顺利进行加密解密
	/*
	RsaParam rsaParam = RsaGetParam();
	m_cParament.d = rsaParam.d;
	m_cParament.e = rsaParam.e;
	m_cParament.n = rsaParam.n;
	PublicKey publicKey = GetPublicKey();
	UINT64 encry = Encry(142, publicKey);
	UINT64 decry = Decry(encry);
	printf("C:%I64u,M:%I64u\n", encry, decry);
	*/
	//UINT64 a = RandomPrime(16);
	//cout << a << endl;
	//UINT64 b = 39103;
	//cout << RabinMiller(b, 30) << endl;
	system("pause");
	return 1;
}