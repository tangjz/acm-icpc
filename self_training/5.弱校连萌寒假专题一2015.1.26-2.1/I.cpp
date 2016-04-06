#include <cstdio>
#include <cstring>
int t, n, m, cnt[1001][4], ans, trans[256];
char str[1001], out[] = "ACGT";
int main()
{
	trans['A'] = 0, trans['C'] = 1, trans['G'] = 2, trans['T'] = 3;
	scanf("%d", &t);
	while(t--)
	{
		memset(cnt, 0, sizeof cnt);
		scanf("%d%d", &m, &n);
		ans = n * m;
		while(m--)
		{
			scanf("%s", str);
			for(int i = 0; i < n; ++i)
				++cnt[i][trans[str[i]]];
		}
		for(int i = 0; i < n; ++i)
		{
			int max = 0;
			for(int j = 1; j < 4; ++j)
				if(cnt[i][max] < cnt[i][j])
					max = j;
			ans -= cnt[i][max];
			putchar(out[max]);
		}
		printf("\n%d\n", ans);
	}
	return 0;
}
