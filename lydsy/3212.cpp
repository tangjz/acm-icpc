/*
 * 区间修改区间求和的简单线段树 
 */
#include <cstdio>
const int maxn = 1 << 18;
int n, m, q;
class XDTree
{
public:
	long long num[maxn], Tree1[maxn << 1], Tree2[maxn << 1];
	void init()
	{
		for(m = 1; m < n; m <<= 1);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%lld", &num[i]);
			Tree1[m + i] = num[i] - num[i - 1];
			Tree2[m + i] = Tree1[m + i] * i;
		}
		for(int i = m - 1; i; --i)
		{
			Tree1[i] = Tree1[i + i] + Tree1[i + i + 1];
			Tree2[i] = Tree2[i + i] + Tree2[i + i + 1];
		}
	}
	void change(int x, long long val)
	{
		int i = x;
		for(Tree1[i += m] += val, Tree2[i] = Tree1[i] * x, i >>= 1; i; i >>= 1)
		{
			Tree1[i] = Tree1[i + i] + Tree1[i + i + 1];
			Tree2[i] = Tree2[i + i] + Tree2[i + i + 1];
		}
	}
	long long query(int t)
	{
		int s = 1;
		long long r = t + 1, ans = 0;
		for(s = s - 1 + m, t = t + 1 + m; s ^ t ^ 1; s >>= 1, t >>= 1)
		{
			if(~s & 1) ans += r * Tree1[s ^ 1] - Tree2[s ^ 1];
			if(t & 1) ans += r * Tree1[t ^ 1] - Tree2[t ^ 1];
		}
		return ans;
	}
} MyTree;
int main()
{
	char type[2];
	int l, r;
	long long x;
	scanf("%d%d", &n, &q);
	MyTree.init();
	while(q--)
	{
		scanf("%s%d%d", type, &l, &r);
		if(type[0] == 'C')
		{
			scanf("%lld", &x);
			MyTree.change(l, x);
			if(r < n) MyTree.change(r + 1, -x);
		}
		else printf("%lld\n", MyTree.query(r) - MyTree.query(l - 1));
	}
	return 0;
}
