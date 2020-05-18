#pragma once
#include <stdlib.h>
#include <stdio.h>
#define UINT64 unsigned __int64

//公钥的结构体，记录了e和n
class PublicKey
{
public:
	unsigned __int64 nE;
	unsigned __int64 nN;
};
class Paraments
{
public:
	unsigned __int64 d;
	unsigned __int64 n;
	unsigned __int64 e;
};
class RsaRaram
{
public:
	unsigned __int64 p;
	unsigned __int64 q;
	unsigned __int64 n;
	unsigned __int64 f;
	unsigned __int64 e;
	unsigned __int64 d;
	unsigned __int64 s;
};

/*
	模的运算
*/
//模乘运算（计算两个数的乘积然后取模）
unsigned __int64 MulMod(unsigned __int64 a, unsigned __int64 b, unsigned __int64 n);
//模幂运算（求模下指数幂的快速算法）
unsigned __int64 PowMod(unsigned __int64 base, unsigned __int64 pow, unsigned __int64 n);

/*
	生成随机的大质数
*/
//Miller-Rabin素数测试算法
long RabinMillerKnl(unsigned __int64 n);
//多次运行Miller-Rabin素数测试算法，以减少误判概率
long RabinMiller(unsigned __int64 &n, long loop = 100);
//最终的质数生成函数
unsigned __int64 RandomPrime(int bits);

/*
	求最大公约数
*/
//通过欧几里得辗转相除法求最大公约数
unsigned __int64 Gcd(unsigned __int64 &p, unsigned __int64 &q);

/*
	私钥生成
*/
//私钥生成，等价于寻找方程e*d = Φ(n)*i+1的整数解
unsigned __int64 Euclid(unsigned __int64 e, unsigned __int64 t_n);

/*
	密钥分配
*/
//加密函数Encry，通过参数cKey传递公钥
unsigned __int64 Encry(unsigned short nSorce, PublicKey &cKey);
//解密函数Decry
unsigned short Decry(UINT64 nSorce);
//公钥获取函数
PublicKey GetPublicKey();
//生成公钥和私钥
RsaRaram RsaGetParam(void);