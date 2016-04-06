#include <cstdio>
#include <cstring>
int n, m, k, f[110][110][110], pos[110][110][110];
int solve(char s[], char t[])
{
	int ans = 0;
	n = strlen(s + 1);
	m = strlen(t + 1);
	memset(f, 0, sizeof f);
	memset(pos, 0, sizeof pos);
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= m; ++j)
			for(int o = 0; o <= k; ++o)
			{
				if(ans < f[i][j][o])
					ans = f[i][j][o];
				if(i < n && (f[i + 1][j][o] < f[i][j][o] || f[i + 1][j][o] == f[i][j][o] && pos[i + 1][j][o] < pos[i][j][o]))
				{
					f[i + 1][j][o] = f[i][j][o];
					pos[i + 1][j][o] = pos[i][j][o];
				}
				if(i < n && j < m && s[i + 1] == t[j + 1])
				{
					int oo = o + (pos[i][j][o] ? i - pos[i][j][o] : 0);
					if(oo <= k && f[i + 1][j + 1][oo] <= f[i][j][o] + 1)
					{
						f[i + 1][j + 1][oo] = f[i][j][o] + 1;
						pos[i + 1][j + 1][oo] = i + 1;
					}
				}
			}
	return ans;
}
int max(int x, int y)
{
	return x < y ? y : x;
}
int main()
{
	char s[110], t[110];
	while(scanf("%s%s%d", s + 1, t + 1, &k) == 3)
		printf("%d\n", max(solve(s, t), solve(t, s)));
	return 0;
}
