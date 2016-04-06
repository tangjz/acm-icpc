#include <queue>
#include <vector>
#include <cstdio>
using namespace std;
const int maxn = 51, INF = 0x3f3f3f3f;
typedef pair<int, int> Edge;
int t, n, dis[maxn];
vector<Edge> e[maxn];
priority_queue<Edge, vector<Edge>, greater<Edge> > Q;
char s[maxn];
bool vis[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%s", s);
			e[i].clear();
			dis[i] = i ? INF : 0;
			vis[i] = 0;
			for(int j = 0, c = 0; j < n; ++j)
				if(s[j] == 'Y')
					e[i].push_back(make_pair(c++, j));
		}
		for( ; !Q.empty(); Q.pop());
		Q.push(make_pair(dis[0], 0));
		while(!Q.empty())
		{
			int u = Q.top().second;
			Q.pop();
			if(vis[u])
				continue;
			vis[u] = 1;
			for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
			{
				int &v = it -> second, &w = it -> first;
				if(dis[v] > dis[u] + w)
				{
					dis[v] = dis[u] + w;
					Q.push(make_pair(dis[v], v));
				}
			}
		}
		printf("%d\n", dis[n - 1] == INF ? -1 : dis[n - 1]);
	}
	return 0;
}
