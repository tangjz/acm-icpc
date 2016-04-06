#include <cstdio>
#include <cstring>
const int maxn = 10;
int t, n, m, ans[maxn];
bool h[maxn][maxn][maxn], v[maxn][maxn][maxn];
int main()
{
	for(int Case = 1; ; ++Case)
	{
		memset(ans, 0, sizeof ans);
		memset(h, 0, sizeof h);
		memset(v, 0, sizeof v);
		if(scanf("%d%d", &n, &m) != 2)
			break;
		for(int i = 0; i < m; ++i)
		{
			char op[2];
			int x, y;
			scanf("%s%d%d", op, &x, &y);
			--x, --y;
			if(op[0] == 'H')
				h[x][y][y + 1] = 1;
			else
				v[x][y][y + 1] = 1;
		}
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				for(int k = j + 2; k < n; ++k)
				{
					h[i][j][k] = h[i][j][k - 1] & h[i][k - 1][k];
					v[i][j][k] = v[i][j][k - 1] & v[i][k - 1][k];
				}
		if(Case > 1)
			puts("\n**********************************\n");
		printf("Problem #%d\n\n", Case);
		bool flag = 0;
		for(int k = 1; k < n; ++k)
		{
			int ans = 0;
			for(int i = 0; i + k < n; ++i)
				for(int j = 0; j + k < n; ++j)
					if(h[i][j][j + k] && h[i + k][j][j + k] && v[j][i][i + k] && v[j + k][i][i + k])
						++ans;
			if(ans)
			{
				printf("%d square (s) of size %d\n", ans, k);
				flag = 1;
			}
		}
		if(!flag)
			puts("No completed squares can be found.");
	}
	return 0;
}
