#include <queue>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int INF = ~0u >> 1;
int n, m, s, t, level[1001], c[1001][1001];
bool bfs()
{
    int i, j;
    memset(level, 0, sizeof(level));
    level[s] = 1;
	queue<int> Q;
    Q.push(s);
    while(!Q.empty())
    {
        i = Q.front(); Q.pop();
        for(j = 1; j <= n; ++j)
            if(c[i][j] > 0 && !level[j])
            {
                level[j] = level[i] + 1;
                Q.push(j);
            }
    }
    return level[t] != 0;
}
int dfs(int u, int flow)
{
    if(u == t) return flow;
    int i, v, w = 0;
    for(v = 1; v <= n; ++v)
        if(c[u][v] > 0 && level[v] == level[u] + 1)
            if(i = dfs(v, min(c[u][v], flow - w)))
            {
                c[u][v] -= i; c[v][u] += i;
                w += i;
            }
    return w;
}
int main()
{
    ios::sync_with_stdio(false);
    int i, u, v, w;
    while(cin >> m >> n)
    {
		memset(c, 0, sizeof(c));
    	s = 1, t = n;
        for(i = 1; i <= m; ++i)
    	{
        	cin >> u >> v >> w;
        	c[u][v] += w;
    	}
    	int cnt = 0;
    	while(bfs())
    	    while((i = dfs(s, INF))) cnt += i;
    	cout << cnt << endl;
    }
    return 0;
}
