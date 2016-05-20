#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 100000, delta = maxn + 2;
int n, a[maxn + 10], tot, seq[maxn], bit[2][maxn + 10], tim[2][maxn + 10], clk;
inline int idx(int x)
{
	return x - (x & 1) + delta >> 1;
}
void add(int o, int x)
{
	for( ; x <= maxn; x += x & -x)
		if(tim[o][x] == clk)
			++bit[o][x];
		else
		{
			tim[o][x] = clk;
			bit[o][x] = 1;
		}
}
int sum(int o, int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		if(tim[o][x] == clk)
			ret += bit[o][x];
	return ret;
}
long long calc(int lim)
{
	int val = 0, pre = 1, cur = 0;
	long long ret = 0;
	++clk;
	add(cur, idx(val));
	for(int i = 1; i <= n; ++i)
	{
		cur ^= 1;
		pre ^= 1;
		val += a[i] >= lim ? 1 : -1;
		ret += sum(pre, idx(val - 1));
		add(cur, idx(val));
	}
	return ret;
}
int main()
{
	long long m;
	scanf("%d%lld", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		seq[tot++] = a[i];
	}
	sort(seq, seq + tot);
	tot = unique(seq, seq + tot) - seq;
	for(int i = 1; i <= n; ++i)
		a[i] = lower_bound(seq, seq + tot, a[i]) - seq;
	int L = 0, R = tot - 1;
	while(L < R)
	{
		int M = L + R + 1 >> 1;
		if(calc(M) < m)
			R = M - 1;
		else
			L = M;
	}
	printf("%d\n", seq[L]);
	return 0;
}
