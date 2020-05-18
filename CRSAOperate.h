#pragma once
#include <stdlib.h>
#include <stdio.h>
#define UINT64 unsigned __int64

//��Կ�Ľṹ�壬��¼��e��n
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
	ģ������
*/
//ģ�����㣨�����������ĳ˻�Ȼ��ȡģ��
unsigned __int64 MulMod(unsigned __int64 a, unsigned __int64 b, unsigned __int64 n);
//ģ�����㣨��ģ��ָ���ݵĿ����㷨��
unsigned __int64 PowMod(unsigned __int64 base, unsigned __int64 pow, unsigned __int64 n);

/*
	��������Ĵ�����
*/
//Miller-Rabin���������㷨
long RabinMillerKnl(unsigned __int64 n);
//�������Miller-Rabin���������㷨���Լ������и���
long RabinMiller(unsigned __int64 &n, long loop = 100);
//���յ��������ɺ���
unsigned __int64 RandomPrime(int bits);

/*
	�����Լ��
*/
//ͨ��ŷ�����շת����������Լ��
unsigned __int64 Gcd(unsigned __int64 &p, unsigned __int64 &q);

/*
	˽Կ����
*/
//˽Կ���ɣ��ȼ���Ѱ�ҷ���e*d = ��(n)*i+1��������
unsigned __int64 Euclid(unsigned __int64 e, unsigned __int64 t_n);

/*
	��Կ����
*/
//���ܺ���Encry��ͨ������cKey���ݹ�Կ
unsigned __int64 Encry(unsigned short nSorce, PublicKey &cKey);
//���ܺ���Decry
unsigned short Decry(UINT64 nSorce);
//��Կ��ȡ����
PublicKey GetPublicKey();
//���ɹ�Կ��˽Կ
RsaRaram RsaGetParam(void);