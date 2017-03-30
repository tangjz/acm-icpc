#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001;
int n, a[maxn], s[maxn], b[maxn], sz, stk[maxn];
int q, qL[maxn], qR[maxn], ord[maxn], ans[maxn];
bool cmp(int const &x, int const &y)
{
	return qR[x] < qR[y];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		s[i] = s[i - 1] + a[i];
		b[i] = i * a[i] - s[i];
	}
	scanf("%d", &q);
	for(int i = 1; i <= q; ++i)
	{
		scanf("%d%d", qL + i, qR + i);
		ord[i] = i;
	}
	sort(ord + 1, ord + q + 1, cmp);
	for(int i = 1, j = 1; i <= n; ++i)
	{
		for( ; sz && a[stk[sz]] >= a[i]; --sz);
		for( ; sz > 1 && (LL)(b[stk[sz]] - b[stk[sz - 1]]) * (a[i] - a[stk[sz]]) >= (LL)(b[i] - b[stk[sz]]) * (a[stk[sz]] - a[stk[sz - 1]]); --sz);
		stk[++sz] = i;
		for( ; j <= q && qR[ord[j]] == i; ++j)
		{
			int o = ord[j], L = 1, R = sz;
			while(L < R)
			{
				int M = (L + R) >> 1;
				int dk = a[stk[M + 1]] - a[stk[M]];
				int db = b[stk[M + 1]] - b[stk[M]];
				if(dk * (qR[o] - qL[o]) <= db)
					R = M;
				else
					L = M + 1;
			}
			ans[o] = b[stk[L]] + s[qR[o]] - a[stk[L]] * (qR[o] - qL[o]);
		}
	}
	for(int i = 1; i <= q; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
