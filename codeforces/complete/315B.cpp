#include <cstdio>
const int maxn = 131072;
class XDTree
{
public:
	int n, m;
	long long Tree[maxn << 2];
	void init()
	{
		for(int i = m - 1; i; --i) Tree[i] = Tree[i + i] + Tree[i + i + 1];
	}
	void change(int n, long long val)
	{
		for(Tree[n += m] += val, n >>= 1; n; n >>= 1)
			Tree[n] = Tree[n + n] + Tree[n + n + 1];
	}
	int query(int s, int t)
	{
		int ans = 0;
		for(s = s - 1 + m, t = t + 1 + m; s ^ t ^ 1; s >>= 1, t >>= 1)
		{
			if(~s & 1) ans += Tree[s ^ 1];
			if(t & 1) ans += Tree[t ^ 1];
		}
		return ans;
	}
} xds;
int q;
long long num[100001];
int main()
{
	int i, j;
	long long x;
	scanf("%d%d", &xds.n, &q);
	for(xds.m = 1; xds.m <= xds.n + 1; xds.m <<= 1);
	for(i = 1; i <= xds.n; ++i)
	{
		scanf("%I64d", &num[i]);
		xds.Tree[xds.m + i] = num[i] - num[i - 1];
	}
	xds.init();
	for(i = 0; i < q; ++i)
	{
		scanf("%I64d", &x);
		if(x == 1)
		{
			scanf("%d%I64d", &j, &x);
			x -= xds.query(1, j);
			xds.change(j, x);
			if(j < xds.n) xds.change(j + 1, -x);
		}
		else if(x == 2)
		{
			scanf("%I64d", &x);
			xds.change(1, x);
		}
		else
		{
			scanf("%I64d", &x);
			printf("%d\n", xds.query(1, x));
		}
	}
	return 0;
}
