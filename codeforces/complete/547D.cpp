#include <set>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 200001;
const char* out = "rb";
int n, x[maxn], y[maxn], ans[maxn];
char str[maxn];
set<int> e[maxn << 1];
void dfs(int u)
{
	int o = 0;
	while(e[u].size() & 1)
	{
		int it = *e[u].begin();
		e[u].erase(it);
		ans[it] = o;
		o ^= 1;
		int v = u < maxn ? maxn + y[it] : x[it];
		e[v].erase(it);
		u = v;
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d", x + i, y + i);
		e[--x[i]].insert(i);
		e[maxn + --y[i]].insert(i);
	}
	memset(ans, -1, sizeof ans);
	for(int i = 0; i < maxn << 1; ++i)
		if(e[i].size() & 1)
			dfs(i);
	for(int i = 0; i < n; ++i)
		if(ans[i] == -1)
		{
			ans[i] = 1;
			e[x[i]].erase(i);
			e[maxn + y[i]].erase(i);
			dfs(x[i]);
		}
	for(int i = 0; i < n; ++i)
		str[i] = out[ans[i]];
	str[n] = '\0';
	puts(str);
	return 0;
}
