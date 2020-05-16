#include <map>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int n, tot, deg[maxn], ans, seq[maxn];
vector<int> e[maxn];
map<vector<int>, int> idx;
map<pair<int, int>, int> Hash;
int getID(const vector<int> &src)
{
	return !idx.count(src) ? idx[src] = ++tot : idx[src];
}
int dfs(int u, int fa)
{
	pair<int, int> cur = make_pair(u, fa);
	if(Hash.count(cur))
		return Hash[cur];
	vector<int> nxt;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		if(*it != fa)
			nxt.push_back(dfs(*it, u));
	sort(nxt.begin(), nxt.end());
	return Hash[cur] = getID(nxt);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		++deg[u];
		++deg[v];
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i = 1; i <= n; ++i)
		if(deg[i] < 4)
			seq[ans++] = dfs(i, -1);
	sort(seq, seq + ans);
	ans = unique(seq, seq + ans) - seq;
	printf("%d\n", ans);
	return 0;
}
