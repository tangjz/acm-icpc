/* 
 * 令f[k,i]表示枚举到第k个工件，在A机器上用i时间，最少在B机器上用f[i]时间 
 * 然后就是奇怪的背包问题了= =...
 * 第一维可以滚动掉 
 */
#include <cstdio>
const int maxn = 6001, maxm = 30001;
int n, m, a[maxn], b[maxn], c[maxn], f[maxm], ans = maxm;
inline int max(int x, int y) { return x < y ? y : x; }
inline int min(int x, int y) { return x < y ? x : y; }
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d%d%d", a + i, b + i, c + i);
		if(!a[i]) a[i] = maxm;
		if(!b[i]) b[i] = maxm;
		if(!c[i]) c[i] = maxm;
		m += min(a[i], min(b[i], c[i]));
	}
	for(int i = 1, tmp; i <= n; ++i)
		for(int j = m; j >= 0; --j)
		{
			tmp = maxm;
			if(j >= a[i]) tmp = min(tmp, f[j - a[i]]);
			tmp = min(tmp, f[j] + b[i]);
			if(j >= c[i]) tmp = min(tmp, f[j - c[i]] + c[i]);
			f[j] = tmp;
		}
	for(int i = 0; i <= m; ++i)
		ans = min(ans, max(i, f[i]));
	printf("%d\n", ans);
	return 0;
}
