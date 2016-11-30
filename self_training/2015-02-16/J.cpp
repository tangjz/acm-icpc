#include <cstdio>
#include <cstring>
const int maxv1 = 501, maxv2 = 51, maxn = 301;
int n, v1, v2, c[maxn], w[maxn], t[maxn], f[maxv1][maxv2][2];
int main()
{
	for(int Case = 1; scanf("%d%d%d", &v1, &v2, &n) == 3 && v1 + v2 + n; ++Case)
	{
		int cnt = 0;
		memset(f, -1, sizeof f);
		for(int i = 0; i < n; ++i)
			scanf("%d%d%d", c + i, w + i, t + i);
		f[0][0][0] = 0;
		for(int i = 0; i < n; ++i)
		{
			if(!t[i])
				continue;
			cnt += w[i];
			for(int j = v1; j >= 0; --j)
				for(int k = v2; k >= 0; --k)
				{
					if(f[j][k][0] != -1 && f[j][k][1] < f[j][k][0] + w[i])
						f[j][k][1] = f[j][k][0] + w[i];
					if(j >= c[i] && f[j - c[i]][k][1] != -1 && f[j][k][1] < f[j - c[i]][k][1] + w[i])
						f[j][k][1] = f[j - c[i]][k][1] + w[i];
					if(k >= c[i] && f[j][k - c[i]][1] != -1 && f[j][k][1] < f[j][k - c[i]][1] + w[i])
						f[j][k][1] = f[j][k - c[i]][1] + w[i];
					if(j >= c[i] && f[j - c[i]][k][0] != -1 && f[j][k][0] < f[j - c[i]][k][0] + w[i])
						f[j][k][0] = f[j - c[i]][k][0] + w[i];
					if(k >= c[i] && f[j][k - c[i]][0] != -1 && f[j][k][0] < f[j][k - c[i]][0] + w[i])
						f[j][k][0] = f[j][k - c[i]][0] + w[i];
				}
		}
		bool flag = 0;
		for(int i = 0; i <= v1; ++i)
			for(int j = 0; j <= v2; ++j)
				for(int k = 0; k < 2; ++k)
					if(f[i][j][k] == cnt)
						flag = 1;
					else
						f[i][j][k] = -1;
		if(!flag)
		{
			printf("Case %d: -1\n\n", Case);
			continue;
		}
		for(int i = 0; i < n; ++i)
		{
			if(t[i])
				continue;
			for(int j = v1; j >= 0; --j)
				for(int k = v2; k >= 0; --k)
				{
					if(f[j][k][0] != -1 && f[j][k][1] < f[j][k][0] + w[i])
						f[j][k][1] = f[j][k][0] + w[i];
					if(j >= c[i] && f[j - c[i]][k][1] != -1 && f[j][k][1] < f[j - c[i]][k][1] + w[i])
						f[j][k][1] = f[j - c[i]][k][1] + w[i];
					if(k >= c[i] && f[j][k - c[i]][1] != -1 && f[j][k][1] < f[j][k - c[i]][1] + w[i])
						f[j][k][1] = f[j][k - c[i]][1] + w[i];
					if(j >= c[i] && f[j - c[i]][k][0] != -1 && f[j][k][0] < f[j - c[i]][k][0] + w[i])
						f[j][k][0] = f[j - c[i]][k][0] + w[i];
					if(k >= c[i] && f[j][k - c[i]][0] != -1 && f[j][k][0] < f[j][k - c[i]][0] + w[i])
						f[j][k][0] = f[j][k - c[i]][0] + w[i];
				}
		}
		for(int i = 0; i <= v1; ++i)
			for(int j = 0; j <= v2; ++j)
				for(int k = 0; k < 2; ++k)
					if(cnt < f[i][j][k])
						cnt = f[i][j][k];
		printf("Case %d: %d\n\n", Case, cnt);
	}
	return 0;
}
