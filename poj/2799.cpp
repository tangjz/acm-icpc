#include <cstdio>
const int maxm = 1001;
int m, ip[maxm][4], maxl, addr[4], mask[4];
int min(int x, int y)
{
	return x < y ? x : y;
}
int max(int x, int y)
{
	return x < y ? y : x;
}
int len(int x)
{
	int ret = 0;
	for( ; x; ++ret, x >>= 1);
	return ret;
}
int main()
{
	while(scanf("%d", &m) == 1)
	{
		for(int i = 0; i < 4; ++i)
			addr[i] = mask[i] = 255;
		for(int i = 0; i < m; ++i)
			for(int j = 0; j < 4; ++j)
			{
				scanf("%*c%d", &ip[i][j]);
				addr[j] &= ip[i][j];
			}
		maxl = 0;
		for(int i = 0; i < m; ++i)
			for(int j = 0; j < 4; ++j)
				if(addr[j] ^ ip[i][j])
					maxl = max(maxl, len(addr[j] ^ ip[i][j]) + (3 - j << 3));
		for(int j = 3; j >= 0; --j)
			if(maxl > 0)
			{
				mask[j] &= ~((1 << min(maxl, 8)) - 1);
				maxl -= 8;
			}
		for(int i = 0; i < 4; ++i)
			printf("%d%c", addr[i] & mask[i], ".\n"[i + 1 == 4]);
		for(int i = 0; i < 4; ++i)
			printf("%d%c", mask[i], ".\n"[i + 1 == 4]);
	}
	return 0;
}