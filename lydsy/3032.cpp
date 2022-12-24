/*
 * 取中位数即可
 */
#include <cstdio>
#include <algorithm>
using namespace std;
long long n, m, t, r[100001] = {}, c[100001] = {}, f[100001] = {};
long long calc(long long p[], int n)
{
	int i;
	long long ans = 0;
	for(i = 1; i <= n; ++i)
	{
		p[i] -= p[0] / n;
		f[i] = f[i - 1] + p[i];
	}
	sort(f + 1,f + n + 1);
	for(i = 1; i <= n; ++i) ans += abs(f[i] - f[(n + 1) >> 1]);
	return ans;
}

int main()
{
	int i, j;
	scanf("%d%d%d", &n, &m, &t);
	while(t--) { scanf("%d%d", &i, &j); ++r[i]; ++c[j]; }
	for(i = 1; i <= n; ++i) r[0] += r[i];
	for(i = 1; i <= m; ++i) c[0] += c[i];
	if(r[0] % n == 0 && c[0] % m == 0) printf("both %lld\n", calc(r, n) + calc(c, m));
	else if(r[0] % n == 0) printf("row %lld\n", calc(r, n));
	else if(c[0] % m == 0) printf("column %lld\n", calc(c, m));
	else printf("impossible\n");
	return 0;
}
