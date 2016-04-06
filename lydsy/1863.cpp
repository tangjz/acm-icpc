#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 20001;
int n, a[maxn], f[maxn], g[maxn];
bool check(int lim)
{
	f[1] = g[1] = a[1];
	for(int i = 2; i <= n; ++i)
	{
		f[i] = min(a[i], a[1] - g[i - 1]);
		g[i] = max(0, a[1] + a[i] + a[i - 1] - f[i - 1] - lim);
	}
	return !g[n];
}
int main()
{
	int L = 0, R, M;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		L = max(L, a[i] + a[i - 1]);
	}
	L = max(L, a[1] + a[n]);
	if(n % 2 == 0)
	{
		printf("%d\n", L);
		return 0;
	}
	R = L * 2;
	while(L < R)
	{
		int M = L + R >> 1;
		if(check(M))
			R = M;
		else
			L = M + 1;
	}
	printf("%d\n", L);
	return 0;
}
