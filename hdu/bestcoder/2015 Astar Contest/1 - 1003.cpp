#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1001, maxm = 51;
int t, n, m;
struct Node
{
	int a, b, c, d;
	bool operator < (const Node &x) const
	{
		if(a != x.a)
			return a < x.a;
		if(b != x.b)
			return b < x.b;
		if(c != x.c)
			return c < x.c;
		return d < x.d;
	}
	bool operator == (const Node &x) const
	{
		return a == x.a && b == x.b && c == x.c && d == x.d;
	}
	Node operator & (const Node &x) const
	{
		return (Node){a & x.a, b & x.b, c & x.c, d & x.d};
	}
	void read()
	{
		scanf("%d.%d.%d.%d", &a, &b, &c, &d);
	}
} ip[maxn], dn, net[maxn];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		printf("Case #%d:\n", Case);
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			ip[i].read();
		for(int i = 0; i < m; ++i)
		{
			dn.read();
			for(int j = 0; j < n; ++j)
				net[j] = ip[j] & dn;
			sort(net, net + n);
			printf("%d\n", unique(net, net + n) - net);
		}
	}
	return 0;
}
