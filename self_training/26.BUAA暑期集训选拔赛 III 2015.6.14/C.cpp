#include <stdio.h>
#include <cstring>
const int maxn = 100001;
int n, m, t, q, r[maxn], c[maxn];
int main()
{
	while(scanf("%d%d%d%d", &n, &m, &t, &q) == 4)
	{
		int x1, y1, x2, y2;
		memset(r, 0, (n + 1) * sizeof(int));
		memset(c, 0, (m + 1) * sizeof(int));
		while(t--)
		{
			scanf("%d%d", &x1, &y1);
			r[x1] = c[y1] = 1;
		}
		for(int i = 2; i <= n; ++i)
			r[i] += r[i - 1];
		for(int i = 2; i <= m; ++i)
			c[i] += c[i - 1];
		while(q--)
		{
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			puts(r[x2] - r[x1 - 1] == x2 - x1 + 1 || c[y2] - c[y1 - 1] == y2 - y1 + 1 ? "Yes" : "No");
		}
	}
	return 0;
}
