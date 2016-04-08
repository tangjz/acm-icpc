#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10001;
int n, t, m, a[maxn], f[maxn], g[maxn], lim;
bool cmp(const int &x, const int &y)
{
	return x > y;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = n; i; --i)
	{
		int j = lower_bound(g + 1, g + lim + 1, a[i], cmp) - g;
		f[i] = j;
		g[j] = a[i];
		if(lim < j)
			lim = j;
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &m);
		if(m > lim)
			puts("Impossible");
		else
			for(int i = 1, j = m, last = ~(~0u >> 1); i <= n && j; ++i)
				if(f[i] >= j && a[i] > last)
				{
					printf("%d%c", a[i], " \n"[!(--j)]);
					last = a[i];
				}
	}
	return 0;
}
