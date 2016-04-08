#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<long long, int> edge;
const int maxn = 100010;
int t, n, m;
long long dis[2][maxn], x[maxn], y[maxn], ans;
vector<edge> e[maxn];
bool vis[2][maxn];
void scan(int &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + ch - '0';
}
int main()
{
	scan(t);
	while(t--)
	{
		ans = 0;
		memset(dis, 0x3f, sizeof dis);
		memset(vis, 0, sizeof vis);
		scan(n), scan(m);
		for(int i = 0; i < n; ++i)
			e[i].clear();
		while(m--)
		{
			int u, v, w;
			scan(u), scan(v), scan(w);
			--u;
			--v;
			e[u].push_back(make_pair(w, v));
			e[v].push_back(make_pair(w, u));
		}
		for(int s = 0; s < 2; ++s)
		{
			priority_queue<edge, vector<edge>, greater<edge> > Q;
			while(!Q.empty())
				Q.pop();
			dis[s][s] = 0;
			Q.push(make_pair(dis[s][s], s));
			while(!Q.empty())
			{
				int u = Q.top().second;
				Q.pop();
				if(vis[s][u])
					continue;
				vis[s][u] = 1;
				for(vector<edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
				{
					int &v = it -> second;
					long long &w = it -> first;
					if(dis[s][v] > dis[s][u] + w)
					{
						dis[s][v] = dis[s][u] + w;
						Q.push(make_pair(dis[s][v], v));
					}
				}
			}
		}
		for(int i = 0; i < n; ++i)
		{
			x[i] = dis[0][i] + dis[1][i]; //2x'
			y[i] = dis[0][i] - dis[1][i]; //2y'
		}
		sort(x, x + n);
		sort(y, y + n);
		long long xx = x[n >> 1], yy = y[n >> 1];
		for(int i = 0; i < n; ++i)
			ans += abs(x[i] - xx) + abs(y[i] - yy);
		printf("%.12f\n", ans / (2.0 * n));
	}
	return 0;
}
