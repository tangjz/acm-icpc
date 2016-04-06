#include <map>
#include <queue>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 101, maxq = 17, maxt = 100;
const double INF = 1e9, eps = 1e-6;
typedef pair<double, int> edge;
map<string, int> idx;
int n, m, q, now, Sta[maxq], End;
double c, T, a[maxq], v[maxq], t[maxq][maxn], dist[maxn];
vector<edge> e[maxn];
priority_queue<edge, vector<edge>, greater<edge> > Q;
char str[100];
bool dijk(double C)
{
	double V = v[now] + a[now] * sqrt(C);
	while(!Q.empty())
		Q.pop();
	fill(dist, dist + n, INF);
	dist[Sta[now]] = 0;
	Q.push(make_pair(dist[Sta[now]], Sta[now]));
	while(!Q.empty())
	{
		int u = Q.top().second;
		Q.pop();
		if(u == End)
			break;
		for(vector<edge>::iterator it = e[u].begin(), jt = e[u].end(); it < jt; ++it)
		{
			int &v = it -> second;
			double &w = it -> first;
			if(dist[v] > dist[u] + w / V + t[now][v])
			{
				dist[v] = dist[u] + w / V + t[now][v];
				Q.push(make_pair(dist[v], v));
			}
		}
	}
	return dist[End] <= T + eps;
}
bool check()
{
	double ret = 0;
	for(now = 0; now < q; ++now)
	{
		double L = 0, R = INF, M;
		for(int tmp = 0; tmp < maxt; ++tmp)
		{
			M = (L + R) / 2;
			if(dijk(M))
				R = M;
			else
				L = M;
		}
		ret += (L + R) / 2;
	}
	return ret <= c + eps;
}
int main()
{
	while(scanf("%d%d%d", &n, &m, &q) == 3)
	{
		idx.clear();
		for(int i = 0; i < n; ++i)
		{
			scanf("%s", str);
			string tmp = str;
			idx[tmp] = i;
			e[i].clear();
		}
		End = idx["Hakurei_Shrine"];
		while(m--)
		{
			scanf("%s", str);
			string tmp = str;
			int u = idx[str];
			scanf("%s", str);
			tmp = str;
			int v = idx[str];
			double w;
			scanf("%lf", &w);
			e[u].push_back(make_pair(w, v));
			e[v].push_back(make_pair(w, u));
		}
		for(int i = 0; i < q; ++i)
		{
			scanf("%*s%s%lf%lf", str, v + i, a + i);
			string tmp = str;
			Sta[i] = idx[tmp];
			for(int j = 0; j < n; ++j)
				scanf("%lf", t[i] + j);
			t[i][End] = 0;
		}
		scanf("%lf", &c);
		double L = 0, R = INF;
		for(int tmp = 0; tmp < maxt; ++tmp)
		{
			T = (L + R) / 2;
			if(check())
				R = T;
			else
				L = T;
		}
		printf("%.8f\n", T = (L + R) / 2);
	}
	return 0;
}
