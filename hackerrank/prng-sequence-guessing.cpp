#include <stdio.h>
typedef long long LL;
class Random
{
	const static int bitLen = 48;
	const static LL multiplier = 0x5DEECE66DL, addend = 0xBL, mask = (1LL << bitLen) - 1;
	LL seed;
	inline int next(int bits)
	{
		seed = (seed * multiplier + addend) & mask;
		return (int)(seed >> (bitLen - bits));
	}
public:
	inline void setSeed(LL newseed)
	{
		newseed = (newseed ^ multiplier) & mask;
		seed = newseed;
	}
	inline int nextInt(int n)
	{
		return next(31) % n;
	}
} Rand;
const int maxn = 10, mod = 1000;
int t, seq[maxn];
LL L, R;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld%lld", &L, &R);
		for(int i = 0; i < maxn; ++i)
			scanf("%d", seq + i);
		for( ; L <= R; ++L)
		{
			bool flag = 1;
			Rand.setSeed(L);
			for(int i = 0; i < maxn && flag; ++i)
				flag &= Rand.nextInt(mod) == seq[i];
			if(flag)
				break;
		}
		printf("%lld", L);
		for(int i = 0; i < maxn; ++i)
			printf(" %d", Rand.nextInt(mod));
		putchar('\n');
	}
	return 0;
}
