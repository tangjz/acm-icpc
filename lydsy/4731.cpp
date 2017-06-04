#include <cstdio>
typedef long long LL;
const int maxn = 10001, maxm = 1000001;
int n, a[maxn], m, lim;
LL b[maxm];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	scanf("%d", &m);
	for(int i = 0; i < m; ++i)
		scanf("%lld", b + i);
	a[n] = m;
	LL pB, cB = 1;
	for(int i = 0; i <= n && cB <= m; ++i)
	{
		if(a[i] == 1)
			continue;
		pB = cB;
		cB *= a[i];
		for(int j = m - 1, r = j % cB; j >= 0; --j, r = (r ? r : cB) - 1)
			if(r >= pB)
				b[j] -= b[j - pB];
	}
	printf("%d\n", n);
	for(int i = 0; i < n; ++i)
		printf("%d%c", a[i], " \n"[i == n - 1]);
	printf("%d\n", m);
	for(int i = 0; i < m; ++i)
		printf("%d%c", (int)b[i], " \n"[i == m - 1]);
	return 0;
}
