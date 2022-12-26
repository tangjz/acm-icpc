#include <cstdio>
const int maxn = 1001, dx[] = {1, 1, -1, -1, 2, 2, -2, -2}, dy[] = {2, -2, 2, -2, 1, -1, 1, -1};
int t, n, m, r[maxn], c[maxn], rc[maxn << 1], cr[maxn << 1], pos[maxn][maxn];
int main()
{
	scanf("%d", &t);
	for(int tim = 1; tim <= t; ++tim)
	{
		scanf("%d%d", &n, &m);
		while(m--)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			r[u] = c[v] = rc[u - v + n] = cr[u + v] = pos[u][v] = tim;
		}
		int ans = 0;
		for(int i = 1; i <= n; ++i)
		{
			if(r[i] == tim)
				continue;
			for(int j = 1; j <= n; ++j)
			{
				if(c[j] == tim || rc[i - j + n] == tim || cr[i + j] == tim)
					continue;
				int cnt = 0;
				for(int o = 0; o < 8; ++o)
				{
					int x = i + dx[o], y = j + dy[o];
					if(1 <= x && x <= n && 1 <= y && y <= n && pos[x][y] == tim)
						++cnt;
				}
				if(cnt >= 2)
					++ans;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
