#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 11;
int n, m, perm[maxn], L[maxn], R[maxn], fa[maxn], match[maxn], inver[maxn], ans;
bool ban[maxn][maxn];
int find(int x)
{
	return fa[x] < 0 ? x : fa[x] = find(fa[x]);
}
bool path(int u, int c)
{
	for(int v = find(1); v < n; v = find(v + 1))
		if((ban[v][perm[u - 1]] || ban[v][perm[u]]) == c)
		{
			fa[v] = find(v + 1);
			if(!match[v] || path(match[v], ban[v][perm[match[v] - 1]] || ban[v][perm[match[v]]]))
			{
				match[v] = u;
				inver[u] = v;
				return 1;
			}
		}
	return 0;
}
void dfs(int dep, int cnt)
{
	if(dep == n)
	{
		cnt += ban[n][perm[0]] || ban[n][perm[n - 1]];
		if(cnt < ans)
			ans = cnt;
		return;
	}
	for(int i = R[0]; i <= n; i = R[i])
	{
		L[R[i]] = L[i];
		R[L[i]] = R[i];
		perm[dep] = i;
		if(dep)
		{
			memset(fa + 1, -1, n * sizeof(int));
			if(!path(dep, 0))
			{
				++cnt;
				for(int j = 1; j < n; ++j)
					if(!match[j] && (ban[j][perm[dep - 1]] || ban[j][perm[dep]]))
					{
						match[j] = dep;
						inver[dep] = j;
						break;
					}
			}
		}
		if(cnt < ans)
			dfs(dep + 1, cnt);
		if(dep)
		{
			cnt -= ban[inver[dep]][perm[dep - 1]] || ban[inver[dep]][perm[dep]];
			match[inver[dep]] = 0;
		}
		L[R[i]] = i;
		R[L[i]] = i;
	}
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		memset(ban, 0, sizeof ban);
		while(m--)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			ban[u][v] = 1;
		}
		R[0] = 1;
		for(int i = 1; i <= n; ++i)
		{
			L[i] = i - 1;
			R[i] = i + 1;
		}
		L[n + 1] = n;
		ans = n;
		dfs(0, 0);
		printf("%d\n", ans);
	}
	return 0;
}
