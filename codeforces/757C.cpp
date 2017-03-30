#include <stdio.h>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef long long LL;
const int maxn = 100001, maxm = 1000001, mod = 1000000007;
const int seed1 = 5145403, mod1 = 1072098169, seed2 = 4558867, mod2 = 1123463261;
int n, m, fact[maxm], tim[maxm], cnt[maxm], tot, que[maxm], h1[maxm], h2[maxm], ans;
namespace std {
	template <>
	struct hash<pair<int, int> > {
		size_t operator () (pair<int, int> const &t) const {
			return ((LL)t.first << 31) ^ t.second;
		}
	};
}
unordered_map<pair<int, int>, int> Hash;
int main()
{
	fact[0] = 1;
	for(int i = 1; i < maxm; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	scanf("%d%d", &n, &m);
	for(int i = 1, sz, x; i <= n; ++i)
	{
		tot = 0;
		scanf("%d", &sz);
		for(int j = 1; j <= sz; ++j)
		{
			scanf("%d", &x);
			if(tim[x] < i)
			{
				tim[x] = i;
				que[++tot] = x;
				cnt[x] = 1;
			}
			else
				++cnt[x];
		}
		for(int j = 1; j <= tot; ++j)
		{
			x = que[j];
			h1[x] = ((LL)h1[x] * seed1 + i) % mod1;
			h1[x] = ((LL)h1[x] * seed1 + cnt[x]) % mod1;
			h2[x] = ((LL)h2[x] * seed2 + i) % mod2;
			h2[x] = ((LL)h2[x] * seed2 + cnt[x]) % mod2;
		}
	}
	for(int i = 1; i <= m; ++i)
		++Hash[make_pair(h1[i], h2[i])];
	ans = 1;
	for(auto &it : Hash)
		ans = (LL)ans * fact[it.second] % mod;
	printf("%d\n", ans);
	return 0;
}
