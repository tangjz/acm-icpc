#include <cstdio>
const int maxa = 1e6 + 1, mod = 1e9 + 7;
int n, pre[maxa], bit[maxa];
void add(int x, int val)
{
	for( ; x < maxa; x += x & -x)
	{
		bit[x] += val;
		if(bit[x] >= mod)
			bit[x] -= mod;
	}
}
int sum(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
	{
		ret += bit[x];
		if(ret >= mod)
			ret -= mod;
	}
	return ret;
}
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		int a, cnt;
		scanf("%d", &a);
		cnt = (long long)a * (sum(a) + 1) % mod;
		add(a, cnt < pre[a] ? cnt - pre[a] + mod : cnt - pre[a]);
		pre[a] = cnt;
	}
	printf("%d\n", sum(maxa - 1));
	return 0;
}
