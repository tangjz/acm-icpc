/*
 * 把大的丢进尽量小的容器里 
 */
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200, maxm = 200;
int n, m, p[maxn], cnt, sum;
struct Node
{
	int c, q;
	bool operator < (const Node &x) const { return q < x.q; }
} b[maxm];
bool cmp(const int &x, const int &y) { return x > y; }
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		if(!n && !m) break;
		cnt = sum = 0;
		for(int i = 0; i < n; ++i)
			scanf("%d", p + i);
		sort(p, p + n, cmp);
		for(int i = 0; i < m; ++i)
			scanf("%d%d", &b[i].c, &b[i].q);
		sort(b, b + m);
		for(int i = 0, j; i < n; ++i)
		{
			for(j = 0; j < m; ++j)
				if(b[j].c && b[j].q >= p[i]) break;
			if(j < m)
			{
				--b[j].c;
				++cnt;
				sum += p[i];
			}
		}
		printf("%d %d\n", cnt, sum);
	}
	return 0;
}
