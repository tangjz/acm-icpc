#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxm = 5, maxs = 100001, mod = 1000000007;
int n, m, a[maxm], tot, inv[maxm << 1 | 1];
struct Node {
	int len, low[maxm], upp[maxm];
	bool operator < (Node const &t) const {
		if(len != t.len)
			return len < t.len;
		for(int i = 0; i < len; ++i)
		{
			if(low[i] != t.low[i])
				return low[i] < t.low[i];
			if(upp[i] != t.upp[i])
				return upp[i] < t.upp[i];
		}
		return 0;
	}
	bool operator == (Node const &t) const {
		if(len != t.len)
			return 0;
		for(int i = 0; i < len; ++i)
		{
			if(low[i] != t.low[i])
				return 0;
			if(upp[i] != t.upp[i])
				return 0;
		}
		return 1;
	}
	Node intersect(Node const &t) const {
		if(len != t.len)
			return (Node){-1};
		Node ret = (Node){len};
		for(int i = 0; i < len; ++i)
		{
			ret.low[i] = std::max(low[i], t.low[i]);
			ret.upp[i] = std::min(upp[i], t.upp[i]);
			if(ret.low[i] > ret.upp[i])
				return (Node){-1};
		}
		return ret;
	}
} seq[maxs], pat;
bool vis[maxm];
void pfs(int dep, int last)
{
	if(dep == m)
	{
		seq[tot++] = pat;
		return;
	}
	// different interval
	for(int i = 0; i < m; ++i)
		if(!vis[i])
		{
			pat.low[pat.len] = pat.upp[pat.len] = a[i];
			++pat.len;
			vis[i] = 1;
			pfs(dep + 1, i);
			vis[i] = 0;
			--pat.len;
			pat.low[pat.len] = pat.upp[pat.len] = 0;
		}
	if(!pat.len)
		return;
	// same interval
	for(int i = last + 1; i < m; ++i)
		if(!vis[i])
		{
			int tlow = pat.low[pat.len - 1], tupp = pat.upp[pat.len - 1];
			pat.low[pat.len - 1] = std::max(tlow, a[i]);
			pat.upp[pat.len - 1] = std::min(tupp + a[i], n);
			vis[i] = 1;
			pfs(dep + 1, i);
			vis[i] = 0;
			pat.low[pat.len - 1] = tlow;
			pat.upp[pat.len - 1] = tupp;
		}
}
int calc(int dep, int val)
{
	if(val <= (pat.len << 1))
		return 0;
	if(dep == pat.len)
	{
		int ret = 1;
		for(int i = 1; i <= (pat.len << 1); ++i)
			ret = (LL)ret * (val - i) % mod * inv[i] % mod;
		return ret;
	}
	int ret = calc(dep + 1, val - pat.low[dep] + 1) - calc(dep + 1, val - pat.upp[dep]);
	if(ret < 0)
		ret += mod;
	return ret;
}
int dfs(int dep, Node cur)
{
	pat = cur;
	int ret = calc(0, n + 2);
	for(int i = dep + 1; i < tot; ++i)
	{
		Node nxt = cur.intersect(seq[i]);
		if(nxt.len == -1)
			continue;
		if((ret -= dfs(i, nxt)) < 0)
			ret += mod;
	}
	return ret;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
		scanf("%d", a + i);
	pfs(0, -1);
	std::sort(seq, seq + tot);
	tot = std::unique(seq, seq + tot) - seq;
	inv[1] = 1;
	for(int i = 2; i <= (m << 1); ++i)
		inv[i] = mod -  (int)(mod / i * (LL)inv[mod % i] % mod);
	int ans = 0;
	for(int i = 0; i < tot; ++i)
		if((ans += dfs(i, seq[i])) >= mod)
			ans -= mod;
	printf("%d\n", ans);
	return 0;
}
