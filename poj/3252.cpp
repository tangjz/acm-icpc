#include <cmath>
#include <cstdio>
const int maxa = 32;
int sta, end, c[maxa][maxa];
int cnt(int n)// Round Numbers in [1, n)
{
	if(n <= 2)
		return 0;
	int ret = 0, len = (int)log2(n) + 1;
	for(int i = 2; i < len; ++i)
	{
		ret += 1 << i - 2;
		if(i & 1)
			ret -= c[i - 1][i - 1 >> 1] >> 1;
	}
	for(int i = len - 2, cnt0 = 0, cnt1 = 1; i >= 0; --i)
		if(n & (1 << i))
		{
			for(int j = i; j >= 0 && j + cnt0 + 1 >= i - j + cnt1; --j)
				ret += c[i][j];
			++cnt1;
		}
		else
			++cnt0;
	return ret;
}
int main()
{
	for(int i = 0; i < maxa; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	while(scanf("%d%d", &sta, &end) == 2)
		printf("%d\n", cnt(end + 1) - cnt(sta));
	return 0;
}
