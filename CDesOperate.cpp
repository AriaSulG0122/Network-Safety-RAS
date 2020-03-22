#include "CDesOperate.h"
#include "StaticArray.h"

INT32 CDesOperate::MakeKey(ULONG32 *keyleft, ULONG32 *keyright, ULONG32 number)
{
	ULONG32 tmpkey[2] = { 0 };
	ULONG32 *Ptmpkey = (ULONG32*)tmpkey;
	ULONG32 *Poutkey = (ULONG32*)&g_outkey[number];
	INT32 j;
	memset((short*)tmpkey, 0, sizeof(tmpkey));
	*Ptmpkey = *keyleft&leftandtab[lefttable[number]];
	Ptmpkey[1] = *keyright&leftandtab[lefttable[number]];
	if (lefttable[number] == 1)//移位为1
	{
		*Ptmpkey >>= 27;
		Ptmpkey[1] >>= 27;
	}
	else//移位为2
	{
		*Ptmpkey >>= 26;
		Ptmpkey[1] >>= 26;
	}
	Ptmpkey[0] &= 0xfffffff0;
	Ptmpkey[1] &= 0xfffffff0;
	*keyleft <<= lefttable[number];
	*keyright <<= lefttable[number];
	*keyleft |= Ptmpkey[0];
	*keyright |= Ptmpkey[1];
	Ptmpkey[0] = 0;
	Ptmpkey[1] = 0;
	for (j = 0; j < 48; j++)
	{
		if (j < 24)
		{
			if (*keyleft&pc_by_bit[keychoose[j] - 1])
			{
				Poutkey[0] |= pc_by_bit[j];
			}
		}
		else /*j>=24*/
		{
			if (*keyright&pc_by_bit[(keychoose[j] - 28)])
			{
				Poutkey[1] |= pc_by_bit[j - 24];
			}
		}
	}
	return SUCCESS;
}
