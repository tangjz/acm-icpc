#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200000;
const long long INF = ~0ull >> 1;
struct Node
{
	long long val;
	int id;
	bool operator < (const Node &x) const
	{
		return val < x.val;
	}
} query[maxn], tmp;
priority_queue<Node> Q;
int t, n, q, delta[maxn];
long long x[maxn], ans[maxn];
template<class T> void Read(T &a)
{
	static int ch, f;
	while(((ch = getchar()) < '0' || ch > '9') && ch != '-');
	f = ch == '-';
	a = ch == '-' ? 0 : ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		a = (a << 3) + (a << 1) + ch - '0';
	a = f ? -a : a;
}
bool cmp(const long long &x, const long long &y)
{
	return x > y;
}
int main()
{
	Read(t);
	for(int Case = 1; Case <= t; ++Case)
	{
		Read(n), Read(q);
		long long lim = (long long)n * (n - 1) >> 1;
		for(int i = 0; i < n; ++i)
			Read(x[i]);
		sort(x, x + n, cmp);
		for(int i = 0; i < n - 1; ++i)
		{
			delta[i] = x[i] >= 0 ? i + 1 : n - 1;
			Q.push((Node){x[i] * x[delta[i]], i});
		}
		for(int i = 0; i < q; ++i)
			Read(query[i].val), query[i].id = i;
		sort(query, query + q);
		for(int i = 0, k = 0; i < q; ++i)
			if(query[i].val > lim)
				ans[query[i].id] = INF;
			else
			{
				while(k < query[i].val)
				{
					tmp = Q.top();
					Q.pop();
					x[tmp.id] >= 0 ? ++delta[tmp.id] : --delta[tmp.id];
					if(delta[tmp.id] > tmp.id && delta[tmp.id] < n)
						Q.push((Node){x[tmp.id] * x[delta[tmp.id]], tmp.id});
					++k;
				}
				ans[query[i].id] = tmp.val;
			}
		printf("Case #%d:\n", Case);
		for(int i = 0; i < q; ++i)
			if(ans[i] == INF)
				puts("SunnyPiggy!Hahaha");
			else
				printf("%lld\n", ans[i]);
		while(!Q.empty())
			Q.pop();
	}
	return 0;
}
