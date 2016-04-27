#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int n, f[maxn], g[maxn], ans;
int main()
{
	scanf("%d", &n);
	memset(g, 0x3f, sizeof g);
	for(int i = 1; i <= n; ++i)
	{
		int x;
		scanf("%d", &x);
		if(x < i)
			continue;
		int k = upper_bound(g + 1, g + i + 1, x - i) - g;
		f[i] = k;
		g[k] = x - i;
		if(ans < f[i])
			ans = f[i];
	}
	printf("%d\n", n - ans);
	return 0;
}
