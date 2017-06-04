#include <stdio.h>
#include <cstring>
const int maxn = 21, maxm = 101, maxs = 1 << 20 | 1, INF = 0x3f3f3f3f;
int n, m, all, f[maxs], cnt[maxs];
inline void upd(int &x, int y)
{
	(x < y) && (x = y);
}
int main()
{
	scanf("%d%d", &n, &m);
	all = (1 << n) - 1;
	for(int i = 1; i <= all; ++i)
	{
		cnt[i] = cnt[i >> 1] + (i & 1);
		f[i] = -INF;
	}
	while(m--)
	{
		int x, y;
		scanf("%d", &x);
		y = 1 << (x - 1);
		for(int i = 1; i <= all; ++i)
			if(i & y)
				upd(f[i], f[i ^ y] + cnt[i >> x]);
	}
	printf("%d\n", f[all]);
	return 0;
}
