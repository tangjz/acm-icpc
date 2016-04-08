#include <map>
#include <bitset>
#include <cstdio>
using namespace std;
const int maxn = 50, mod = 1000000007;
map<int, int> Hash;
bitset<maxn << 3> a[maxn];
int t, n, x, tot, ans;
int index(int x)
{
	return Hash.count(x) ? Hash[x] : Hash[x] = tot++;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		tot = 0;
		Hash.clear();
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", &x);
			a[i].reset();
			for(int j = 2, k; j <= x / j; ++j)
				if(x % j == 0)
				{
					for(k = 0; x % j == 0; x /= j, ++k);
					if(k & 1)
						a[i][index(j)] = 1;
				}
			if(x > 1)
				a[i][index(x)] = 1;
		}
		ans = 0;
		for(int i = 0, j, k; i < n; ++i)
		{
			for(j = 0; j < tot && !a[i][j]; ++j);
			if(j == tot)
				continue;
			for(k = i + 1; k < n; ++k)
				if(a[k][j])
					a[k] ^= a[i];
			++ans;
		}
		printf("%lld\n", 1LL << ans);
	}
	return 0;
}
