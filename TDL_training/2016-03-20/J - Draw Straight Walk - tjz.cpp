#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int n, pre[maxn], r[maxn], L, R, que[maxn];
int mid[maxn], dep[maxn];
int len[maxn], dep_len[maxn], delta[maxn];
int e[maxn][2];
void dfs(int u, int R)
{
	int L = u + 1, M = r[u];
	if(L < M)
	{
		e[u][0] = L;
		dep[L] = dep[u] + 1;
		dfs(L, M);
	}
	if(M < R)
	{
		e[u][1] = M;
		dep[M] = dep[u] + 1;
		dfs(M, R);
	}
}
int last_len;
void pfs(int u)
{
	if(e[u][0] != -1)
		pfs(e[u][0]);
	delta[u] = last_len - dep_len[dep[u]];
	len[u] = last_len + (pre[u] ? (int)log10(pre[u]) + 1 : 1);
	last_len = dep_len[dep[u]] = len[u];
	if(e[u][1] != -1)
		pfs(e[u][1]);
}
int main()
{
	for( ; scanf("%d", pre + n) != EOF; ++n);
	for(int i = n - 1; i >= 0; --i)
	{
		while(R > 0 && pre[que[R - 1]] < pre[i])
			--R;
		r[i] = R > 0 ? que[R - 1] : n;
		que[R++] = i;
	}
	memset(e, -1, sizeof e);
	dfs(0, n);
	pfs(0);
	L = R = 0;
	que[R++] = 0;
	int last_dep = 0;
	while(L < R)
	{
		int u = que[L++];
		if(last_dep < dep[u])
		{
			putchar('\n');
			last_dep = dep[u];
		}
		for(int i = 0; i < delta[u]; ++i)
			putchar(' ');
		printf("%d", pre[u]);
		if(e[u][0] != -1)
			que[R++] = e[u][0];
		if(e[u][1] != -1)
			que[R++] = e[u][1];
	}
	return 0;
}
