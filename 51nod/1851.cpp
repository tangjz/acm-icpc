#include <stdio.h>
const int maxn = 10000001;
int t, n, m;
char buf[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		if(n >= 2 && m >= 2 && (n > 2 || m > 2))
		{
			int cnt = 0;
			while(n--)
			{
				scanf("%s", buf);
				for(int i = 0; i < m; ++i)
					cnt += buf[i] == '1';
			}
			puts(!(cnt & 1) ? "Yes" : "No");
		}
		else if(n == 2 && m == 2)
		{
			int cnt = 0;
			while(n--)
			{
				scanf("%s", buf);
				for(int i = 0; i < m; ++i)
					cnt += buf[i] == '1';
			}
			puts(!(cnt & 3) ? "Yes" : "No");
		}
		else
		{
			int cnt[4] = {};
			for(int i = 0; i < n; ++i)
			{
				scanf("%s", buf);
				for(int j = 0; j < m; ++j)
					cnt[(i + j) & 3] ^= buf[j] == '1';
			}
			puts(cnt[0] == cnt[1] && cnt[1] == cnt[2] && cnt[2] == cnt[3] ? "Yes" : "No");
		}
	}
	return 0;
}
