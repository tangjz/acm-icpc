/*
 * 第一行的翻转决定其他行
 * 暴搜翻法第一行，其他行贪心即可
 */
#include <cstdio>
#include <cstring>
const int INF = ~0u >> 1;
int n, m, a[20], op[20], b[20], aop[20], st, all, ans = INF, cnt;
int calc(int x)
{
	int s = 0;
	while(x)
	{
		s += x & 1;
		x >>= 1;
	}
	return s;
}
int main()
{
	int i, j, t;
	scanf("%d%d", &n, &m);
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= m; ++j)
		{
			scanf("%d", &t);
			a[i] = (a[i] << 1) + t;
		}
	all = (1 << m) - 1;
    for(st = 0; st <= all; ++st)
	{
		memcpy(b, a, sizeof(a));
		j = 1; op[1] = st; cnt = calc(st);
		b[j + 1] ^= op[j];
		for(j = 2; j <= n + 1; ++j)
		{
			op[j] = (b[j - 1] ^ op[j - 1] ^ (op[j - 1] >> 1) ^ ((op[j - 1] << 1) & all)) & all;
			b[j + 1] ^= op[j];
			cnt += calc(op[j]);
		}
		if(!op[n + 1] && cnt < ans)
		{
			ans = cnt;
			memcpy(aop, op, sizeof(op));
		}
	}
	if(ans == INF) puts("IMPOSSIBLE");
	else
		for(i = 1; i <= n; ++i)
		{
			for(j = m - 1; j; --j) printf("%d ", (aop[i] >> j) & 1);
			printf("%d\n", aop[i] & 1);
		}
	return 0;
}
