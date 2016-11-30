#include <bitset>
#include <stdio.h>
using namespace std;
typedef unsigned long long ULL;
const int maxn = 50001, maxs = ((maxn - 1) >> 6) + 1;
int n, m, bits[1 << 16], brev[16][1 << 16];
ULL f[maxs], g[maxs];
char buf[maxn];
inline ULL mask(int len) // 1 <= len <= 64
{
	return (len < 64 ? 1ULL << len : 0ULL) - 1;
}
inline ULL getbits(ULL f[], int pL, int pR) // f[pL : pR] (pR - pL + 1 <= 64)
{
	return (pL >> 6) == (pR >> 6) ? (f[pL >> 6] >> (pL & 63)) & mask(pR - pL + 1) :
	(f[pR >> 6] & mask((pR & 63) + 1)) << (((pR >> 6) << 6) - pL) | (f[pL >> 6] >> (pL & 63));
}
inline void putbits(ULL f[], int pL, int pR, ULL msk) // (pR - pL + 1 <= 64)
{
	if((pL >> 6) == (pR >> 6))
		f[pL >> 6] ^= (((f[pL >> 6] >> (pL & 63)) & mask(pR - pL + 1)) ^ msk) << (pL & 63);
	else
	{
		putbits(f, pL, ((pR >> 6) << 6) - 1, msk & mask(((pR >> 6) << 6) - pL));
		putbits(f, (pR >> 6) << 6, pR, msk >> (((pR >> 6) << 6) - pL));
	}
}
inline int countbits(ULL msk)
{
	int ret = 0;
	for( ; msk; msk >>= 16)
		ret += bits[msk & ((1 << 16) - 1)];
	return ret;
}
inline ULL reversebits(ULL msk, int len)
{
	ULL ret = 0;
	for( ; len > 0; len -= 16, msk >>= 16)
	{
		int blen = len < 16 ? len : 16;
		ret = ret << blen | brev[blen - 1][msk & ((1 << blen) - 1)];
	}
	return ret;
}
int main()
{
	for(int i = 1; i < 1 << 16; ++i)
		bits[i] = bits[i >> 1] + (i & 1);
	for(int i = 0; i < 16; ++i)
		for(int j = 0; j < 1 << (i + 1); ++j)
			brev[i][j] = (brev[i][j >> 1] >> 1) | ((j & 1) << i);
	scanf("%d%s", &n, buf);
	for(int i = 0; i < n; ++i)
		if(buf[i] == 'b')
			f[i >> 6] |= 1ULL << (i & 63);
	scanf("%d", &m);
	while(m--)
	{
		int L, R;
		scanf("%s%d%d", buf, &L, &R);
		--L, --R;
		switch(buf[0])
		{
			case 'C' : {
				scanf("%s", buf);
				for(int i = L >> 6; i <= (R >> 6); ++i)
				{
					int pL = i == (L >> 6) ? (L & 63) : 0;
					int pR = i == (R >> 6) ? (R & 63) : 63;
					ULL msk = mask(pR - pL + 1) << pL;
					buf[0] == 'b' ? f[i] |= msk : f[i] &= ~msk;
				}
				break;
			}
			case 'S' : {
				int L2, R2, sz = 0;
				scanf("%d%d", &L2, &R2);
				--L2, --R2;
				for(int i = L2; i <= R2; i += 64)
				{
					int j = i + 63 <= R2 ? i + 63 : R2;
					putbits(g, sz, sz + j - i, getbits(f, i, j));
					sz += j - i + 1;
				}
				for(int i = R + 1; i < L2; i += 64)
				{
					int j = i + 63 < L2 ? i + 63 : L2 - 1;
					putbits(g, sz, sz + j - i, getbits(f, i, j));
					sz += j - i + 1;
				}
				for(int i = L; i <= R; i += 64)
				{
					int j = i + 63 <= R ? i + 63 : R;
					putbits(g, sz, sz + j - i, getbits(f, i, j));
					sz += j - i + 1;
				}
				for(int i = L; i <= R2; i += 64)
				{
					int j = i + 63 <= R2 ? i + 63 : R2;
					putbits(f, i, j, getbits(g, i - L, j - L));
				}
				break;
			}
			case 'R' : {
				for(int i = R; i >= L; i -= 64)
				{
					int j = i - 63 >= L ? i - 63 : L;
					putbits(g, R - i, R - j, reversebits(getbits(f, j, i), i - j + 1));
				}
				for(int i = L; i <= R; i += 64)
				{
					int j = i + 63 <= R ? i + 63 : R;
					putbits(f, i, j, getbits(g, i - L, j - L));
				}
				break;
			}
			case 'W' : {
				for(int i = L; i <= R; ++i)
					buf[i - L] = "ab"[(f[i >> 6] >> (i & 63)) & 1];
				buf[R - L + 1] = '\0';
				puts(buf);
				break;
			}
			case 'H' : {
				int len, ctr = 0;
				scanf("%d", &len);
				for(int i = 0; i < len; i += 64)
				{
					int j = i + 63 < len ? i + 63 : len - 1;
					ULL msk1 = getbits(f, L + i, L + j);
					ULL msk2 = getbits(f, R + i, R + j);
					ctr += countbits(msk1 ^ msk2);
				}
				printf("%d\n", ctr);
				break;
			}
		}
	}
	return 0;
}
