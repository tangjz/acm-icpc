#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 100001, maxs = 510001, maxd = 26;
struct Trie {
	int cnt, nxt[maxd];
} e[maxs];
char str[maxs];
int n, tot, sz[maxn];
long long ans;
std::vector<int> g[maxn];
bool cmp(int const &x, int const &y)
{
	return sz[x] < sz[y];
}
int pfs(int u, int pid)
{
	int ppid = pid;
	if(e[u].cnt > 0)
	{
		g[pid].push_back(++tot);
		pid = tot;
	}
	int cnt = 0;
	for(int i = 0; i < maxd; ++i)
		if(e[u].nxt[i])
			cnt += pfs(e[u].nxt[i], pid);
	if(ppid != pid)
		sz[pid] += cnt++;
	return cnt;
}
void dfs(int u, int pid)
{
	ans += (++tot) - pid;
	pid = tot;
	std::sort(g[u].begin(), g[u].end(), cmp);
	for(std::vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it)
		dfs(*it, pid);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%s", str);
		int rt = 0;
		for(int j = strlen(str) - 1; j >= 0; --j)
		{
			str[j] -= 'a';
			if(!e[rt].nxt[str[j]])
				e[rt].nxt[str[j]] = ++tot;
			rt = e[rt].nxt[str[j]];
		}
		e[rt].cnt = 1;
	}
	tot = 0;
	pfs(0, 0);
	tot = 0;
	std::sort(g[0].begin(), g[0].end(), cmp);
	for(std::vector<int>::iterator it = g[0].begin(); it != g[0].end(); ++it)
		dfs(*it, 0);
	printf("%lld\n", ans);
	return 0;
}
