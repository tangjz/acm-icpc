#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 1;
int n;
double ans;
struct Node
{
	int a, b, d;
	bool operator < (const Node &x) const
	{
		return d < x.d;
	}
} f[maxn];
priority_queue<pair<int, int> > Q;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d%d", &f[i].a, &f[i].b, &f[i].d);
	sort(f, f + n);
	for(int i = 0, now = 0; i < n; ++i)
	{
		Q.push(make_pair(f[i].a, f[i].b));
		now += f[i].b;
		while(!Q.empty() && now > f[i].d)
		{
			pair<int, int> tmp = Q.top();
			Q.pop();
			int delta = min(tmp.second, now - f[i].d);
			now -= delta;
			tmp.second -= delta;
			ans += (double)delta / tmp.first;
			if(tmp.second)
				Q.push(tmp);
		}
	}
	printf("%.2f\n", ans);
	return 0;
}