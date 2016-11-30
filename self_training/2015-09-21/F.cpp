#include <cstdio>
#include <cstring>
const int maxn = 101;
int f[maxn][maxn][maxn], g[maxn][maxn][maxn];
bool dfs(int p, int q, int r)
{
	if(f[p][q][r] != -1)
		return f[p][q][r];
	bool flag = 0;
	for(int i = 1; i < p && !flag; ++i)
	{
		int tp = i, tq = q < i ? q : i, tr = r < i ? r : i;
		flag |= !dfs(tp, tq, tr);
		if(flag)
			g[p][q][r] = (i + 1) * 3;
	}
	for(int i = 0; i < q && !flag; ++i)
	{
		int tp = p, tq = i, tr = r < i ? r : i;
		flag |= !dfs(tp, tq, tr);
		if(flag)
			g[p][q][r] = (i + 1) * 3 + 1;
	}
	for(int i = 0; i < r && !flag; ++i)
	{
		int tp = p, tq = q, tr = i;
		flag |= !dfs(tp, tq, tr);
		if(flag)
			g[p][q][r] = (i + 1) * 3 + 2;
	}
	return f[p][q][r] = flag;
}
int main()
{
	memset(f, -1, sizeof f);
	f[1][0][0] = 0;
	int t, id, p, q, r;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d", &id, &p, &q, &r);
		if(!dfs(p, q, r))
			printf("%d L\n", id);
		else
			printf("%d W %d %d\n", id, g[p][q][r] / 3, g[p][q][r] % 3 + 1);
	}
	return 0;
}
