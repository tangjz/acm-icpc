#include <cstdio>
#include <cstring>
const int maxn = 15, maxm = 101, maxs = 26;
int n, m, pos[maxs], u[maxm][2], e[maxn][maxn], g[1 << maxn], p[1 << maxn], dep[maxn];
bool f[1 << maxn];
char chr[maxn];
int main()
{
	while(scanf("%d", &m) == 1)
	{
		n = 0;
		memset(pos, -1, sizeof pos);
		memset(e, -1, sizeof e);
		for(int i = 0; i < m; ++i)
		{
			char op[2];
			for(int j = 0; j < 2; ++j)
			{
				scanf("%s", op);
				op[0] -= 'A';
				if(pos[op[0]] == -1)
				{
					chr[n] = op[0] + 'A';
					pos[op[0]] = n++;
				}
				u[i][j] = pos[op[0]];
			}
			e[u[i][0]][u[i][1]] = e[u[i][1]][u[i][0]] = 1;
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
			f[s] = 0;
			for(int i = 0; i < n; ++i)
				if((t & (1 << i)) && e[i][g[x]] != -1)
				{
					f[s] = 1;
					break;
				}
		}
		for(int s = 1; s < 1 << n; ++s)
		{
			g[s] = n + 1;
			for(int t = s; t; t = (t - 1) & s)
				if(!f[t] && g[s] > g[s ^ t] + 1)
				{
					g[s] = g[s ^ t] + 1;
					p[s] = t;
				}
		}
		for(int s = (1 << n) - 1, t = p[s], cnt = 0; t; s ^= t, t = p[s], ++cnt)
			for(int i = 0; i < n; ++i)
				if(t & (1 << i))
					dep[i] = cnt;
		printf("%d\n", g[(1 << n) - 1] - 2);
		for(int i = 0; i < m; ++i)
			if(dep[u[i][0]] < dep[u[i][1]])
				printf("%c %c\n", chr[u[i][0]], chr[u[i][1]]);
			else
				printf("%c %c\n", chr[u[i][1]], chr[u[i][0]]);
	}
	return 0;
}
