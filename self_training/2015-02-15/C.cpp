#include <cstdio>
const int maxn = 1e4 + 1;
int n, q, cnt[maxn];
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", cnt + i);
		cnt[i] += cnt[i - 1];
	}
	while(q--)
	{
		int x, l = 1, r = n + 1, m;
		scanf("%d", &x);
		while(l < r)
		{
			m = l + r >> 1;
			if(cnt[m] > x)
				r = m;
			else
				l = m + 1;
		}
		printf("%d\n", l);
	}
	return 0;
}
