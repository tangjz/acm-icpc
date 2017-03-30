#include <cstdio>
const int maxn = 1000001;
int n, m, bit[maxn];
void add(int x, int v)
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
	scanf("%d%d", &n, &m);
	if(m > n - m)
		m = n - m;
	long long ans = 1;
	for(int i = 1, pre = 1, cur = pre + m; i <= n; ++i)
	{
		int nxt = cur + m - 1;
		if(nxt > n)
			nxt -= n;
		ans += sum(nxt) - sum(pre) + (pre < nxt ? 1 : i);
		printf("%I64d%c", ans, " \n"[i == n]);
		add(cur, 1);
		pre = cur;
		if((cur += m) > n)
			cur -= n;
	}
	return 0;
}
