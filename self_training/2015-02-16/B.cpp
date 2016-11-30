#include <cstdio>
#include <cstring>
const int maxv = 51, maxm = 1001;
int n, m, s[maxv], f[maxm];
int main()
{
	while(scanf("%d", &n) != EOF && n)
	{
		memset(s, 0, sizeof s);
		memset(f, -1, sizeof f);
		for(int i = 0, x; i < n; ++i)
		{
			scanf("%d", &x);
			++s[x];
		}
		scanf("%d", &m);
		if(m < 5)
		{
			printf("%d\n", m);
			continue;
		}
		int maxc = 0;
		for(int i = 50; i > 0; --i)
			if(s[i])
			{
				maxc = i;
				--s[i];
				break;
			}
		f[0] = 0;
		for(int i = 1; i <= 50; ++i)
			for(int j = 0; j <= m - 5; ++j)
				if(f[j] >= 0)
					f[j] = s[i];
				else if(j >= i && f[j - i] > 0)
					f[j] = f[j - i] - 1;
		for(int i = m - 5; i >= 0; --i)
			if(f[i] >= 0)
			{
				printf("%d\n", m - i - maxc);
				break;
			}
	}
	return 0;
}
