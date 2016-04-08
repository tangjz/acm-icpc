/*
ID: tangjin2
LANG: C++
TASK: comehome
*/
#include <map>
#include <queue>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
const int INF = 100000;
typedef pair<int, int> edge;
map<char, int> number;
vector<char> name;
vector<int> dis;
vector<edge> g[53];
priority_queue<edge, vector<edge>, greater<edge> > Q;
int n = 1, m;
bool visited[53] = {};
int transformed(char s)
{
	if(number[s]) return number[s];
	name.push_back(s);
	return number[s] = ++n;
}
int main()
{
	freopen("comehome.in", "r", stdin);
	freopen("comehome.out", "w", stdout);
	int i, u, v, w, maxn, tmp;
	char ch;
	scanf("%d", &m);
	number['Z'] = n = 1;
	name.push_back('\0');
	name.push_back('Z');
	for(i = 0; i < m; ++i)
	{
		while((ch = getchar()) < 'A' || (ch > 'Z' && ch < 'a') || ch > 'z');
		u = transformed(ch);
		while((ch = getchar()) < 'A' || (ch > 'Z' && ch < 'a') || ch > 'z');
		v = transformed(ch);
		scanf("%d", &w);
		g[u].push_back(make_pair(w, v));
		g[v].push_back(make_pair(w, u));
	}
	dis.assign(n + 1, INF);
	dis[1] = 0;
	maxn = (int)g[1].size();
	for(i = 0; i < maxn; ++i) if(dis[g[1][i].second] > g[1][i].first) dis[g[1][i].second] = g[1][i].first;
	for(i = 2; i <= n; ++i) Q.push(make_pair(dis[i], i));
	visited[1] = true;
	for(int j = 2; j < n; ++j)
	{
		do
		{
			u = Q.top().second;
			Q.pop();
		} while(visited[u]);
		visited[u] = true;
		maxn = (int)g[u].size();
		for(i = 0; i < maxn; ++i)
		{
			tmp = dis[u] + g[u][i].first;
			v = g[u][i].second;
			if(tmp < dis[v])
			{
				dis[v] = tmp;
				Q.push(make_pair(tmp, v));
			}
		}
	}
	for(tmp = 0, i = 2; i <= n; ++i) if('A' <= name[i] && name[i] <= 'Z' && dis[i] < dis[tmp]) tmp = i;
	printf("%c %d\n", name[tmp], dis[tmp]);
}
