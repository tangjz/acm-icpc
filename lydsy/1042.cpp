/*
 * 预处理出1~maxn的方案数 回答询问用容斥原理
 */
#include <cstdio>
const int maxn = 100001;
int tot, c[4], d[4], s;
long long f[maxn], ans;
inline long long F(const int &x) { return x >= 0 ? f[x] : 0; }
int main()
{
	int i, j;
	scanf("%d%d%d%d%d", &c[0], &c[1], &c[2], &c[3], &tot);
	f[0] = 1;
	for(i = 0; i < 4; ++i)
		for(j = c[i]; j < maxn; ++j) f[j] += f[j - c[i]];
	while(tot--)
	{
		scanf("%d%d%d%d%d", &d[0], &d[1], &d[2], &d[3], &s);
		printf("%lld\n", F(s) - F(s - (d[0] + 1) * c[0]) - F(s - (d[1] + 1) * c[1]) - F(s - (d[2] + 1) * c[2]) - F(s - (d[3] + 1) * c[3]) + F(s - (d[0] + 1) * c[0] - (d[1] + 1) * c[1]) + F(s - (d[0] + 1) * c[0] - (d[2] + 1) * c[2]) + F(s - (d[0] + 1) * c[0] - (d[3] + 1) * c[3]) + F(s - (d[1] + 1) * c[1] - (d[2] + 1) * c[2]) + F(s - (d[1] + 1) * c[1] - (d[3] + 1) * c[3]) + F(s - (d[2] + 1) * c[2] - (d[3] + 1) * c[3]) - F(s - (d[0] + 1) * c[0] - (d[1] + 1) * c[1] - (d[2] + 1) * c[2]) - F(s - (d[0] + 1) * c[0] - (d[1] + 1) * c[1] - (d[3] + 1) * c[3]) - F(s - (d[0] + 1) * c[0] - (d[2] + 1) * c[2] - (d[3] + 1) * c[3]) - F(s - (d[1] + 1) * c[1] - (d[2] + 1) * c[2] - (d[3] + 1) * c[3]) + F(s - (d[0] + 1) * c[0] - (d[1] + 1) * c[1] - (d[2] + 1) * c[2] - (d[3] + 1) * c[3]));
	}
	return 0;
}
