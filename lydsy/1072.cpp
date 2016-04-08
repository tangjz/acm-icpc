#include <cstdio>
#include <cstring>
const int maxn = 10, maxd = 1000;
int t, n, d, fact[maxn + 1], c[maxn], f[1 << maxn][maxd], ans;
char s[maxn];
int main()
{
	fact[0] = 1;
	for(int i = 1; i <= maxn; ++i)
		fact[i] = fact[i - 1] * i;
	scanf("%d", &t);
	while(t--)
	{
		memset(c, 0, sizeof c);
		memset(f, 0, sizeof f);
		scanf("%s%d", s, &d);
		n = strlen(s);
		for(int i = 0; i < n; ++i)
		{
			s[i] -= '0';
			++c[s[i]];
		}
		f[0][0] = 1;
		for(int i = 0; i < 1 << n; ++i)
			for(int j = 0; j < d; ++j)
				if(f[i][j])
					for(int k = 0; k < n; ++k)
						if(!(i & (1 << k)))
							f[i | 1 << k][(j * 10 + s[k]) % d] += f[i][j];
		ans = f[(1 << n) - 1][0];
		for(int i = 0; i < maxn; ++i)
			ans /= fact[c[i]];
		printf("%d\n", ans);
	}
	return 0;
}
