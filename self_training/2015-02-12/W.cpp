#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 2001;
int n, m, dfs_t, tot, id[maxn], pre[maxn], top, stack[maxn];
int val[maxn], size[maxn], f[maxn], ans[maxn], maxans;
vector<int> e1[maxn], e2[maxn];
int tarjan(int u, int fa)
{
	int lowu = pre[u] = ++dfs_t, lowv;
	stack[top++] = u;
	for(vector<int>::iterator it = e1[u].begin(); it != e1[u].end(); ++it)
	{
		int &v = *it;
		if(v == fa)
			continue;
		if(!pre[v])
		{
			lowv = tarjan(v, u);
			if(lowu > lowv)
				lowu = lowv;
		}
		else if(lowu > pre[v])
			lowu = pre[v];
	}
	if(lowu == pre[u])
	{
		++tot;
		while(1)
		{
			int p = stack[--top];
			id[p] = tot;
			++val[tot];
			if(p == u)
				break;
		}
	}
	return lowu;
}
void dfs(int u, int fa)
{
	size[u] = val[u];
	ans[u] = 0;
	for(vector<int>::iterator it = e2[u].begin(); it != e2[u].end(); ++it)
	{
		int &v = *it;
		if(v == fa)
			continue;
		dfs(v, u);
		size[u] += size[v];
		ans[u] += ans[v];
	}
	ans[u] += val[u] * size[u];
}
int main()
{
	scanf("%d%d", &n, &m);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e1[u].push_back(v);
		e1[v].push_back(u);
	}
	tarjan(1, 0);
	for(int i = 1; i <= n; ++i)
		for(vector<int>::iterator it = e1[i].begin(); it != e1[i].end(); ++it)
			if(id[i] < id[*it])
			{
				e2[id[i]].push_back(id[*it]);
				e2[id[*it]].push_back(id[i]);
			}
	for(int i = 1; i <= tot; ++i)
	{
		dfs(i, 0);
		memset(f, 0, sizeof f);
		f[0] = 1;
		for(vector<int>::iterator it = e2[i].begin(); it != e2[i].end(); ++it)
			for(int j = size[i] - val[i]; j >= size[*it]; --j)
				f[j] |= f[j - size[*it]];
		int tmp = 0;
		for(int j = 1; j <= size[i] - val[i]; ++j)
			if(f[j] && tmp < j * (size[i] - val[i] - j))
				tmp = j * (size[i] - val[i] - j);
		ans[i] += tmp;
		if(maxans < ans[i])
			maxans = ans[i];
	}
	printf("%d\n", maxans);
	return 0;
}

