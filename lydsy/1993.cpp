#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 300, mod = 7;
const char *days[] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
int n, m, inv[mod], mat[maxn][maxn + 1];
int main()
{
	inv[1] = 1;
	for(int i = 2; i < mod; ++i)
		inv[i] = mod - mod / i * inv[mod % i] % mod;
	while(scanf("%d%d", &n, &m) == 2 && n + m)
	{
		for(int i = 0; i < m; ++i)
		{
			int cnt, x;
			char sa[4], sb[4];
			memset(mat[i], 0, (n + 1) * sizeof(int));
			scanf("%d%s%s", &cnt, sa, sb);
			while(cnt--)
			{
				scanf("%d", &x);
				if(++mat[i][--x] >= mod)
					mat[i][x] -= mod;
			}
			++mat[i][n];
			for(int j = 0; days[j]; ++j)
				if(!strcmp(sb, days[j]))
				{
					if((mat[i][n] += j) >= mod)
						mat[i][n] -= mod;
					break;
				}
			for(int j = 0; days[j]; ++j)
				if(!strcmp(sa, days[j]))
				{
					if((mat[i][n] -= j) < 0)
						mat[i][n] += mod;
					break;
				}
		}
		int r = 0;
		for(int i = 0, j, k; i < n; ++i)
		{
			for(j = r; j < m; ++j)
				if(mat[j][i])
					break;
			if(j == m)
				continue;
			for(k = i; k <= n; ++k)
				std::swap(mat[r][k], mat[j][k]);
			for(j = 0; j < m; ++j)
				if(r != j && mat[j][i])
				{
					int d = mat[j][i] * inv[mat[r][i]] % mod;
					for(k = i; k <= n; ++k)
						if((mat[j][k] = (mat[j][k] - d * mat[r][k]) % mod) < 0)
							mat[j][k] += mod;
				}
			++r;
		}
		bool flag = 0;
		for(int i = r; i < m && !flag; ++i)
			flag |= mat[i][n];
		if(flag)
			puts("Inconsistent data.");
		else if(r < n)
			puts("Multiple solutions.");
		else
			for(int i = 0; i < n; ++i)
			{
				int val = mat[i][n] * inv[mat[i][i]] % mod;
				printf("%d%c", val < 3 ? val + 7 : val, " \n"[i == n - 1]);
			}
	}
	return 0;
}
