#include <stdio.h>
#include <cstring>
typedef unsigned long long ULL;
const int maxm = 1 << 16, maxd = 10, maxs = 1000001, BLEN = ((maxs - 1) >> 6) + 2;
char str[maxs];
int t, n, sz, bits[maxm | 1];
ULL bit[maxd + 1][BLEN], *ans = bit[maxd];
inline void setBit(ULL bit[BLEN], int pos, bool val)
{
	int px = pos >> 6, py = pos & 63;
	if((((bit[px]) >> py) & 1) ^ val)
		bit[px] ^= 1ULL << py;
}
inline void shiftLeft(ULL bit[BLEN], int sta, int dt)
{
	int sp = sta >> 6, dx = dt >> 6, dy = dt & 63, dz = -dy & 63;
	bit[sz + dx] = 0;
	for(int i = sz - 1, j = i + dx; i > sp; --i, --j)
	{
		if(dz)
			bit[j + 1] |= bit[i] >> dz;
		bit[j] = bit[i] << dy;
	}
	ULL msk = bit[sp] & ((~0ULL) << (sta & 63)); // upp
	if(dz)
		bit[sp + dx + 1] |= msk >> dz;
	if(dx)
		bit[sp + dx] = msk << dy;
	else
		bit[sp] = msk << dy | (bit[sp] ^ msk);
}
inline void shiftRight(ULL bit[BLEN], int sta, int dt)
{
	int sp = sta >> 6, dx = dt >> 6, dy = dt & 63, dz = -dy & 63;
	ULL msk = bit[sp] & ((1ULL << (sta & 63)) - 1); // low
	bit[sp] ^= msk;
	bit[sz] = 0;
	for(int i = sp, j = i + dx; j < sz; ++i, ++j)
	{
		bit[i] = bit[j] >> dy;
		if(dz)
			bit[i] |= bit[j + 1] << dz;
	}
	bit[sp] = (bit[sp] & ((~0ULL) << (sta & 63))) | msk;
}
int main()
{
	for(int i = 1; i < maxm; ++i)
		bits[i] = bits[i >> 1] + (i & 1);
	scanf("%d", &t);
	while(t--)
	{
		int typ, L, R;
		scanf("%d", &typ);
		if(typ == 0)
		{
			scanf("%d%s", &L, str);
			int sLen = strlen(str);
			for(int i = 0, ch = '0'; i < maxd; ++i, ++ch)
			{
				shiftLeft(bit[i], L, sLen);
				for(int j = 0, k = L; j < sLen; ++j, ++k)
					setBit(bit[i], k, str[j] == ch);
			}
			n += sLen;
			sz = ((n - 1) >> 6) + 1;
		}
		else if(typ == 1)
		{
			scanf("%d%d", &L, &R);
			int sLen = R - L;
			for(int i = 0; i < maxd; ++i)
				shiftRight(bit[i], L, sLen);
			n -= sLen;
			sz = ((n - 1) >> 6) + 1;
		}
		else // typ == 2
		{
			scanf("%d%d%s", &L, &R, str);
			int sLen = strlen(str);
			if(R - L < sLen)
			{
				puts("0");
				continue;
			}
			int pL = L >> 6, pR = (R - 1) >> 6;
			memcpy(ans + pL, bit[(int)(str[0] - '0')] + pL, (pR - pL + 1) * sizeof(ULL));
			ans[pL] &= (~0ULL) << (L & 63);
			for(int i = 1; i < sLen; ++i)
			{
				for(int j = pR; j > pL; --j)
					ans[j] = ans[j] << 1 | (ans[j - 1] >> 63);
				ans[pL] <<= 1;
				ULL *cur = bit[(int)(str[i] - '0')];
				for(int j = pL; j <= pR; ++j)
					ans[j] &= cur[j];
			}
			ans[pR] &= (~0ULL) >> (~(R - 1) & 63);
			int res = 0, dt = 16, msk = (1 << dt) - 1;
			for(int i = pL; i <= pR; ++i)
				for( ; ans[i]; res += bits[ans[i] & msk], ans[i] >>= dt);
			printf("%d\n", res);
		}
	}
	return 0;
}
