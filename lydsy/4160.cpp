#include <cstdio>
const int maxn = 15, maxs = 26;
int n, m, pos[maxs], g[1 << maxn];
bool e[maxn][maxn], f[1 << maxn];
int main()
{
	scanf("%d", &m);
	while(m--)
	{
		int u[2];
		char op[2];
		for(int i = 0; i < 2; ++i)
		{
			scanf("%s", op);
			op[0] -= 'A';
			if(!pos[op[0]])
				pos[op[0]] = ++n;
			u[i] = pos[op[0]] - 1;
		}
		e[u[0]][u[1]] = e[u[1]][u[0]] = 1;
	}
	for(int i = 0; i < n; ++i)
		g[1 << i] = i;
	for(int s = 1; s < 1 << n; ++s)
	{
		int x = s & -s, t = s ^ x;
		if(f[t])
		{
			f[s] = 1;
			continue;
		}
		for(int i = 0; i < n; ++i)
			if((t & (1 << i)) && e[i][g[x]])
			{
				f[s] = 1;
				break;
			}
	}
	for(int s = 1; s < 1 << n; ++s)
	{
		g[s] = n;
		for(int t = s; t > 0; t = (t - 1) & s)
			if(!f[t] && g[s] > g[s ^ t] + 1)
				g[s] = g[s ^ t] + 1;
	}
	printf("%d\n", g[(1 << n) - 1] - 2);
	return 0;
}
