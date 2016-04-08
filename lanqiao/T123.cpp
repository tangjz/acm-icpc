#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 100001, maxm = 1000001;
int n, h[maxn], bit[maxm], d[maxn];
LL ans;
void add(int x, int v)
{
	for( ; x < maxm; x += ~x & x + 1)
		bit[x] += v;
}
int sum(int x)
{
	int ret = 0;
	for( ; x >= 0; x -= ~x & x + 1)
		ret += bit[x];
	return ret;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", h + i);
	for(int i = 1; i <= n; ++i)
	{
		d[i] += i - 1 - sum(h[i]);
		add(h[i], 1);
	}
	memset(bit, 0, sizeof bit);
	for(int i = n; i >= 1; --i)
	{
		d[i] += sum(h[i] - 1);
		add(h[i], 1);
		ans += d[i] * (d[i] + 1LL) >> 1;
	}
	printf("%I64d\n", ans);
	return 0;
}
