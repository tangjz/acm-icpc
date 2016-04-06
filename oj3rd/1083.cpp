#include <cstdio>
#include <cstring>
const int maxn = 100010;
int n, m, a[maxn], bit[maxn], delta;
long long f[maxn];
void add(int x)
{
	for( ; x <= n; x += x & -x)
		++bit[x];
}
int sum(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		f[0] = delta = 0;
		memset(bit, 0, sizeof bit);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", a + i);
			add(a[i]);
			f[0] += i - sum(a[i] - 1);
		}
		for(int i = 1; i < n; ++i)
			f[i] = f[i - 1] + sum(a[n - i] - 1) * 2 - n + 1;
		while(m--)
		{
			char op[2];
			int x;
			scanf("%s", op);
			if(op[0] == 'Q')
				printf("%lld\n", f[delta]);
			else
			{
				scanf("%d", &x);
				delta = (delta + x) % n;
			}
		}
	}
	return 0;
}
