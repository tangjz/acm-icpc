#include <stack>
#include <vector>
#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 100001, maxd = 18, mod = 1000000007;
int t, n, m, a[maxn], tot, que[maxn];
std::vector<int> e[maxn];
int sz, seq[maxn], in[maxn], out[maxn];
int seg_tot, root[maxn];
struct Segment {
	int lch, rch, cnt, prod;
} seg[maxn * maxd | 1];
void update(int &rt, int L, int R, int x)
{
	int last = rt;
	seg[rt = ++seg_tot] = seg[last];
	++seg[rt].cnt;
	seg[rt].prod = (LL)seg[rt].prod * que[x] % mod;
	if(L == R)
		return;
	int M = L + R >> 1;
	if(x <= M)
		update(seg[rt].lch, L, M, x);
	else
		update(seg[rt].rch, M + 1, R, x);
}
int mod_inv(int x)
{
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			std::vector<int>().swap(e[i]);
		for(int i = 2; i <= n; ++i)
		{
			int fa;
			scanf("%d", &fa);
			e[fa].push_back(i);
		}
		tot = 0;
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			que[tot++] = a[i];
		}
		std::sort(que, que + tot);
		tot = std::unique(que, que + tot) - que;
		sz = 0;
		{ // dfs
			std::stack<std::pair<int, std::vector<int>::iterator> > S;
			seq[++sz] = 1;
			in[1] = sz;
			S.push(std::make_pair(1, e[1].begin()));
			while(!S.empty())
			{
				std::pair<int, std::vector<int>::iterator> &state = S.top();
				int &u = state.first;
				std::vector<int>::iterator &it = state.second;
				if(it != e[u].end())
				{
					int v = *it;
					++it;
					seq[++sz] = v;
					in[v] = sz;
					S.push(std::make_pair(v, e[v].begin()));
				}
				else
				{
					out[u] = sz;
					S.pop();
				}
			}
		}
		seg_tot = 0;
		seg[0] = (Segment){0, 0, 0, 1};
		for(int i = 1; i <= n; ++i)
		{
			root[i] = root[i - 1];
			update(root[i], 0, tot - 1, std::lower_bound(que, que + tot, a[seq[i]]) - que);
		}
		int ans = 0;
		for(int i = 1; i <= n; ++i)
		{
			int rtL = root[in[i] - 1], rtR = root[out[i]], L = 0, R = tot - 1;
			int rem = std::min(m, out[i] - in[i] + 1), fz = 1, fm = 1;
			while(L < R)
			{
				int M = L + R >> 1, cR = seg[seg[rtR].rch].cnt - seg[seg[rtL].rch].cnt;
				if(cR < rem)
				{
					fz = (LL)fz * seg[seg[rtR].rch].prod % mod;
					fm = (LL)fm * seg[seg[rtL].rch].prod % mod;
					rem -= cR;
					rtL = seg[rtL].lch;
					rtR = seg[rtR].lch;
					R = M;
				}
				else
				{
					rtL = seg[rtL].rch;
					rtR = seg[rtR].rch;
					L = M + 1;
				}
			}
			if(rem)
				fz = (LL)fz * mod_pow(que[L], rem) % mod;
			ans = (ans + (LL)fz * mod_inv(fm)) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
