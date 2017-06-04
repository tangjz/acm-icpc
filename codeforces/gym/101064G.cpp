#include <cstdio>
const int maxn = 100001, maxd = 17;
int n, tot, a[maxn], dep[maxn], pos[maxn], fa[maxd][maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		char op[3];
		int v, x;
		scanf("%s", op);
		if(op[0] == 'E')
		{
			scanf("%d%d", &v, &x);
			a[++tot] = x;
			fa[0][tot] = pos[v];
			for(int i = 0; fa[i][tot]; ++i)
				fa[i + 1][tot] = fa[i][fa[i][tot]];
			dep[i] = dep[v] + 1;
			pos[i] = tot;
		}
		else
		{
			scanf("%d", &v);
			dep[i] = dep[v] - 1;
			pos[i] = pos[v];
			int idx = pos[i];
			for(int j = dep[i], d = 0; j; j >>= 1, ++d)
				(j & 1) && (idx = fa[d][idx]);
			printf("%d\n", a[idx]);
		}
	}
	return 0;
}
