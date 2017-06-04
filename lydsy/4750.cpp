#include <stdio.h>
typedef long long LL;
const int maxt = 201, maxs = 1000001, maxv = 1000000001;
const int maxn = 100001, maxd = 31, mod = 1000000061, INF = 0x3f3f3f3f;
int t, n, a[maxn + 2], mx, s[maxd][maxn], sz, stk[maxn], L[maxn], R[maxn], ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		mx = 0;
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			for( ; 1 << mx <= a[i]; ++mx);
		}
		for(int i = 1, v = 0; i <= n; ++i)
		{
			v ^= a[i];
			for(int j = 0; j < mx; ++j)
				s[j][i] = s[j][i - 1] + ((v >> j) & 1);
		}
		sz = 0;
		a[0] = INF;
		stk[sz++] = 0;
		for(int i = 1; i <= n; ++i)
		{
			for( ; a[stk[sz - 1]] <= a[i]; --sz);
			L[i] = stk[sz - 1] + 1;
			stk[sz++] = i;
		}
		sz = 0;
		a[n + 1] = INF;
		stk[sz++] = n + 1;
		for(int i = n; i >= 1; --i)
		{
			for( ; a[stk[sz - 1]] < a[i]; --sz);
			R[i] = stk[sz - 1] - 1;
			stk[sz++] = i;
		}
		ans = 0;
		for(int i = 1; i <= n; ++i)
		{
			int sum = 0;
			for(int j = 0; j < mx; ++j)
			{
				int cL = i - L[i] + 1, sL = s[j][i - 1] - (L[i] > 1 ? s[j][L[i] - 2] : 0);
				int cR = R[i] - i + 1, sR = s[j][R[i]] - s[j][i - 1];
				sum = (sum + (((LL)sL * (cR - sR) + (LL)sR * (cL - sL)) << j)) % mod;
			}
			ans = (ans + (LL)sum * a[i]) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
