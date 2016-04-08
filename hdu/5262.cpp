#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010, mod = 1000000007;
int t, n, f[maxn], g[maxn], pre[26], ans, sum;
char str[maxn];
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		printf("Case #%d:\n", Case);
		scanf("%s", str + 1);
		n = strlen(str + 1);
		ans = sum = 0;
		memset(pre, 0, sizeof pre);
		memset(f, 0x3f, sizeof f);
		memset(g, 0, sizeof g);
		f[0] = 0;
		g[0] = 1;
		for(int i = 1; i <= n + 1; ++i)
		{
			for(int j = 0; j < 26; ++j)
				if(f[i] > f[pre[j]] + 1)
				{
					f[i] = f[pre[j]] + 1;
					g[i] = g[pre[j]];
				}
				else if(f[i] == f[pre[j]] + 1)
					inc(g[i], g[pre[j]]);
			if(i <= n)
				pre[str[i] - 'a'] = i;
		}
		printf("%d %d\n", f[n + 1], g[n + 1]);
	}
	return 0;
}
