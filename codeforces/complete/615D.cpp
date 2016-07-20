#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
typedef long long LL;
typedef double DB;
typedef long double LDB;
const int maxn = 200010;
const int mod = 1000000007, mod2 = 1000000006;
int n, p, a[maxn], f[maxn], pre[maxn], suf[maxn], ans;
int mod_pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % mod;
		x = (LL)x * x % mod;
		k >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	sort(a + 1, a + n + 1);
	{
		int tot = 0;
		for(int i = 1; i <= n; ++i)
		{
			if(a[i - 1] != a[i])
				a[++tot] = a[i];
			++f[tot];
		}
		n = tot;
	}
	pre[0] = 1;
	for(int i = 1; i <= n; ++i)
		pre[i] = (LL)pre[i - 1] * (f[i] + 1) % mod2;
	suf[n + 1] = 1;
	for(int i = n; i; --i)
		suf[i] = (LL)suf[i + 1] * (f[i] + 1) % mod2;
	ans = 1;
	for(int i = 1; i <= n; ++i)
	{
		int exp = (LL)(f[i] + 1) * f[i] / 2 % mod2 * pre[i - 1] % mod2 * suf[i + 1] % mod2;
		ans = (LL)ans * mod_pow(a[i], exp) % mod;
	}
	printf("%d\n", ans);
	return 0;
}
