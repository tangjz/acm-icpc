#include <vector>
#include <stdio.h>
using namespace std;
const int maxn = 1000001, mod = 998244353;
int n, mx, cnt[maxn], pw[maxn], f[maxn];
bool vis[maxn];
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		int x;
		scanf("%d", &x);
		cnt[x] = 1;
		vis[x] = 1;
		if(mx < x)
			mx = x;
	}
	pw[0] = 1;
	for(int i = 1; i <= mx; ++i)
	{
		pw[i] = 2LL * pw[i - 1] % mod;
		for(int j = i + i; j <= mx; j += i)
			cnt[i] += cnt[j];
	}
	int ans = 0;
	for(int i = mx; i > 0; --i)
	{
		f[i] = pw[cnt[i]] - cnt[i] - 1;
		if(f[i] < 0)
			f[i] += mod;
		for(int j = i + i; j <= mx; j += i)
			if((f[i] -= f[j]) < 0)
				f[i] += mod;
		if(f[i] || vis[i])
			++ans;
	}
	printf("%d\n", ans);
	return 0;
}
