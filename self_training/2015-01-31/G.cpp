#include <cstdio>
const int maxn = 400, maxx = 10086, mod = 1000000000;
struct BigInt
{
	int len, num[maxn];
	void write()
	{
		printf("%d", num[len - 1]);
		for(int i = len - 2; i >= 0; --i)
			printf("%09d", num[i]);
		putchar('\n');
	}
	BigInt operator * (int x) const
	{
		BigInt tmp = *this;
		for(int i = 0; i < len; ++i)
			tmp.num[i] *= x;
		for(int i = 0; i < len; ++i)
			if(tmp.num[i] >= mod)
			{
				tmp.num[i + 1] += tmp.num[i] / mod;
				tmp.num[i] %= mod;
			}
		while(tmp.num[tmp.len])
		{
			if(tmp.num[tmp.len] >= mod)
			{
				tmp.num[tmp.len + 1] = tmp.num[tmp.len] / mod;
				tmp.num[tmp.len] %= mod;
			}
			++tmp.len;
		}
		return tmp;
	}
} pow2[maxx];
int t, n, m;
int main()
{
	pow2[0].len = pow2[0].num[0] = 1;
	for(int i = 1; i < maxx; ++i)
		pow2[i] = pow2[i - 1] * 2;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		if(((n + m) & 1) == 0)
			pow2[(n - 1) * (m - 1)].write();
		else
			puts("0");
	}
	return 0;
}

