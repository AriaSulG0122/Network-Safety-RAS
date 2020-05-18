#include"CRSAOperate.h"


Paraments m_cParament;

//ģ�����㣨�����������ĳ˻�Ȼ��ȡģ��
unsigned __int64 MulMod(unsigned __int64 a, unsigned __int64 b, unsigned __int64 n) {
	return (a%n)*(a%n) % n;
}
//ģ�����㣨��ģ��ָ���ݵĿ����㷨��
unsigned __int64 PowMod(unsigned __int64 base, unsigned __int64 pow, unsigned __int64 n) {
	unsigned __int64 c = 1;
	while (pow) {
		while (!(pow & 1)) {//ĩλΪ0����powΪż��
			pow >>= 1;//pow����
			base = MulMod(base, base, n);
		}
		//����ĩλΪ1����Ϊ��������--���ٴ�ѭ��ĩλΪ0
		pow--;
		c = MulMod(base, c, n);
	}
	return c;
}


//Miller-Rabin���������㷨
long RabinMillerKnl(unsigned __int64 &n) {
	unsigned __int64 a, q, k, v;
	q = n - 1;
	k = 0;
	//ʹn-1=q*2^k������qΪ����
	while (!(q & 1)) {//q��ĩλΪ0����qΪż��
		++k;
		q >>= 1;
	}
	//���ѡȡ1<a<n-1
	a = 2 + rand() % (n - 3);
	v = PowMod(a, q, n);
	if (v == 1) {//���a^q mod n == 1�������Ϊ����
		return 1; 
	}
	//������ԣ���������1<=j<=k-1����a^(q*2^j) mod n != -1����nΪ����
	for (int j = 0; j < k; j++) {
		unsigned int z = 1;
		//�õ�z=2^j
		for (int w = 0; w < j; w++) {
			z << 1;
		}
		if (PowMod(a, z*q, n) == n - 1) {//����Ϊ����
			return 1;
		}
		return 0;
	}
}
//�������Miller-Rabin���������㷨���Լ������и���
long RabinMiller(unsigned __int64 &n, long loop ) {
	for (long i = 0; i < loop; i++) {
		if (!RabinMillerKnl(n)) {//��ĳ��Miller-Rabin���������в�ͨ������nΪ����
			return 0;
		}
	}
	//ͨ����loop�ֲ��ԣ���Ϊ����
	return 1;
}
//���յ��������ɺ���������bitsλ������
unsigned __int64 RandomPrime(char bits) {
	unsigned __int64 base;
	do {
		base = (unsigned long)1 << (bits - 1);//��֤���λ��1
		base += rand()%base;//�ټ���һ�������
		base |= 1;//��֤���λ��1������֤������
	} while (!RabinMiller(base, 30));//����Miller-Rabin��������30��
	return base;//ÿ��Miller-Rabin�������Զ�ͨ������Ϊ����
}


//ͨ��ŷ�����շת����������Լ��
unsigned __int64 Gcd(unsigned __int64 &p, unsigned __int64 &q){
	unsigned __int64 a = p > q ? p : q;//�õ�p��q�еĽϴ�ֵ
	unsigned __int64 b = p < q ? p : q;//�õ�p��q�еĽ�Сֵ
	unsigned __int64 t;
	if (p == q) {
		return p;//��ȣ���Լ����������
	}
	else {
		while (b) {//շת�����
			a = a%b;
			t = a;
			a = b;
			b = t;
		}
		return a;
	}
}

//˽Կ���ɣ��ȼ���Ѱ�ҷ���e*d = ��(n)*i+1��������
unsigned __int64 Euclid(unsigned __int64 e, unsigned __int64 t_n) {
	unsigned __int64 Max = 0xffffffffffffffff - t_n;
	unsigned __int64 i = 1;
	while (1) {
		if (((i*t_n) + 1) % e == 0) {
			return ((i*t_n) + 1) / e;
		}
		i++;
		unsigned __int64 Tmp = (i + 1)*t_n;
		if (Tmp > Max) {//�������ֵ�����ټ���
			return 0;
		}
	}
	return 0;
}

//���ܺ���Encry��ͨ������cKey���ݹ�Կ
static unsigned __int64 Encry(unsigned short nSorce, PublicKey &cKey) {
	return PowMod(nSorce, cKey.nE, cKey.nN);//nSorceΪ����
}
//���ܺ���Decry
unsigned short Decry(UINT64 nSorce) {
	UINT64 nRes = PowMod(nSorce, m_cParament.d, m_cParament.n);
	unsigned short *pRes = (unsigned short*)&(nRes);//�õ�nRes�ĵ�ַ
	if (pRes[1] != 0 || pRes[2] != 0 || pRes[3] != 0) {
		return 0;//���ܺ�õ�16λ�����֣����������ֽڱ�ȻΪ�գ��������
	}
	else {
		return pRes[0];
	}
}
//��Կ��ȡ����
PublicKey GetPublicKey(){
	PublicKey cTmp;
	cTmp.nE = m_cParament.e;
	cTmp.nN = m_cParament.n;
	return cTmp;
}

//���ɹ�Կ��˽Կ
RsaRaram RsaGetParam(void) {
	RsaRaram Rsa = { 0 };
	UINT64 t;
	Rsa.p = RandomPrime(16);
	Rsa.q = RandomPrime(16);
	Rsa.n = Rsa.p*Rsa.q;
	Rsa.f = (Rsa.p - 1)*(Rsa.q - 1);
	do {//����e��f����
		Rsa.e = rand() % 65536;
		Rsa.e |= 1;
	} while (Gcd(Rsa.e, Rsa.f) != 1);
	Rsa.d = Euclid(Rsa.e, Rsa.f);
	Rsa.s = 0;//��¼n��λ��
	t = Rsa.n >> 1;
	while (t) {
		Rsa.s++;
		t >>= 1;
	}
	return Rsa;
}
