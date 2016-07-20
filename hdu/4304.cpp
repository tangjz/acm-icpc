#include <cmath>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <functional>
typedef long long LL;
const int maxp = 1000004, maxn = 4358, maxd = 40, maxs = 12, delta = 6, mod = 960991;
int HashCounter, lnk[mod];
struct Hash
{
	int nxt;
	LL val;
} e[maxn];
inline bool getNewID(LL val, int &idx)
{
	int pos = val % mod;
	for(int it = lnk[pos]; it != -1; it = e[it].nxt)
		if(e[it].val == val)
		{
			idx = it;
			return 0;
		}
	e[HashCounter] = (Hash){lnk[pos], val};
	idx = HashCounter;
	lnk[pos] = HashCounter++;
	return 1;
}
struct FactExp
{
	int len, cnt[maxs];
	void sort()
	{
		std::sort(cnt, cnt + len, std::greater<int>());
		for( ; len && !cnt[len - 1]; --len);
	}
	int omega() const
	{
		int ret = 0;
		for(int i = 0; i < len; ++i)
			ret += cnt[i];
		return ret;
	}
	LL hash() const
	{
		LL ret = 0;
		for(int i = len - 1; i >= 0; --i)
			ret = ret << delta | cnt[i];
		return ret;
	}
	bool nextSubFact(FactExp &t) const
	{
		int i;
		for(i = 0; i < len && t.cnt[i] == cnt[i]; ++i)
			t.cnt[i] = 0;
		++t.cnt[i];
		if(i)
			return 1;
		for( ; i < len && t.cnt[i] == cnt[i]; ++i);
		return i < len;
	}
};
int sz[maxn];
LL f[maxn][maxd];
int dfs(FactExp u)
{
	int uID;
	u.sort();
	if(!getNewID(u.hash(), uID))
		return uID;
	sz[uID] = u.omega() + 1;
	FactExp v = {u.len};
	do
	{
		int vID = dfs(v);
		for(int i = 0; i < sz[vID]; ++i)
			f[uID][i + 1] += f[vID][i];
	} while(u.nextSubFact(v));
	return uID;
}
int tot, prime[maxp >> 3];
bool vis[maxp];
FactExp getFactExp(LL n)
{
	FactExp ret = {};
	for(int i = 0, lim = (int)sqrt(n); prime[i] <= lim; ++i)
		if(n % prime[i] == 0)
		{
			for( ; n % prime[i] == 0; n /= prime[i], ++ret.cnt[ret.len]);
			++ret.len;
			lim = (int)sqrt(n);
		}
	if(n > 1)
		ret.cnt[ret.len++] = 1;
	return ret;
}
int main()
{
	for(int i = 2; i < maxp; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0, k = (maxp - 1) / i; j < tot && prime[j] <= k; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	int t;
	memset(lnk, -1, sizeof lnk);
	getNewID(0, t);
	sz[0] = 1;
	f[0][0] = 1;
	scanf("%d", &t);
	while(t--)
	{
		int nID;
		LL n, val = 0;
		scanf("%I64d", &n);
		if(n == 1)
		{
			puts("1");
			continue;
		}
		nID = dfs(getFactExp(n));
		for(int i = 1; i < sz[nID]; ++i)
			val += f[nID][i] * (f[nID][i - 1] + f[nID][i]);
		printf("%I64d\n", val << 1);
	}
	return 0;
}
