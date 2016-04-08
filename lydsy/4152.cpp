#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair<LL, int> edge;
const int maxn = 200001;
int n;
LL dis[maxn];
vector<edge> e[maxn];
priority_queue<edge, vector<edge>, greater<edge> > Q;
bool vis[maxn];
struct Point
{
	int id, x, y;
} p[maxn];
bool cmp1(const Point &a, const Point &b)
{
	return a.x < b.x || a.x == b.x && a.y < b.y;
}
bool cmp2(const Point &a, const Point &b)
{
	return a.y < b.y || a.y == b.y && a.x < b.x;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		p[i].id = i + 1;
		scanf("%d%d", &p[i].x, &p[i].y);
	}
	sort(p, p + n, cmp1);
	for(int i = 1; i < n; ++i)
	{
		int &u = p[i - 1].id, &v = p[i].id, w = p[i].x - p[i - 1].x;
		e[u].push_back(make_pair(w, v));
		e[v].push_back(make_pair(w, u));
	}
	sort(p, p + n, cmp2);
	for(int i = 1; i < n; ++i)
	{
		int &u = p[i - 1].id, &v = p[i].id, w = p[i].y - p[i - 1].y;
		e[u].push_back(make_pair(w, v));
		e[v].push_back(make_pair(w, u));
	}
	memset(dis, 0x3f, sizeof dis);
	dis[1] = 0;
	Q.push(make_pair(dis[1], 1));
	while(!Q.empty())
	{
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		vis[u] = 1;
		for(vector<edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		{
			int &v = it -> second;
			LL &w = it -> first;
			if(dis[v] > dis[u] + w)
			{
				dis[v] = dis[u] + w;
				Q.push(make_pair(dis[v], v));
			}
		}
	}
	printf("%lld\n", dis[n]);
	return 0;
}
