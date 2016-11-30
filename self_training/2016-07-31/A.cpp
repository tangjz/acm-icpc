#include <cstdio>
#include <cstring>
const int maxn = 20001;
int t, n, m, sqr[maxn];
int calc(int len)
{
	int ret = 0;
	for(int i = 0; i * i <= len; ++i)
		if(sqr[len - i * i] != -1)
		{
			int p = i, q = sqr[len - i * i];
			bool f1 = (n * p + m * q) % len == 0 && (n * q - m * p) % len == 0;
			bool f2 = (n * p - m * q) % len == 0 && (n * q + m * p) % len == 0;
			if(f1)
				++ret;
			if(p > 0 && f2)
				++ret;
			if(q > 0 && f2)
				++ret;
			if(p > 0 && q > 0 && f1)
				++ret;
		}
	return ret;
}
int main()
{
	memset(sqr, -1, sizeof sqr);
	for(int i = 0; i * i < maxn; ++i)
		sqr[i * i] = i;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		int len = n * n + m * m, cnt = 0;
		for(int i = 1; i * i <= len; ++i)
			if(len % i == 0)
			{
				cnt += calc(i);
				if(i * i < len)
					cnt += calc(len / i);
			}
		puts(cnt == 8 ? "P" : "C");
	}
	return 0;
}
