#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200001;
int n, p[maxn], f[maxn], g[maxn], mx, h[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1, x; i <= n; ++i)
	{
		scanf("%d", &x);
		p[x] = i;
	}
	for(int i = 1, j; i <= n; ++i)
	{
		j = lower_bound(h + 1, h + mx + 1, p[i]) - h;
		h[j] = p[i];
		f[i] = j;
		if(mx < j)
			mx = j;
	}
	mx = 0;
	for(int i = n, j; i >= 1; --i)
	{
		j = lower_bound(h + 1, h + mx + 1, p[i]) - h;
		h[j] = p[i];
		g[i] = j;
		if(mx < j)
			mx = j;
	}
	mx = 0;
	for(int i = 1; i <= n; ++i)
		if(mx < f[i] + g[i] - 1)
			mx = f[i] + g[i] - 1;
	printf("%d\n", mx);
	return 0;
}
