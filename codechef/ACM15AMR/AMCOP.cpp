#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 50001, maxm = 100001, maxs = 3200001, mod = 1000000007, maxe = 7, maxp = 65;
int fact[maxn], iact[maxn], tot, pr[maxm], d[maxm], idx, cnt, pp[maxe];
int c[maxm], s[maxn], pos[maxn], qtot, que[maxs];
int n, q, sqn, sz[maxn], lpos[maxn], ord[maxn], ans[maxn];
std::pair<int, int> a[maxn][maxp];
struct Query {
	int l, r, k;
} query[maxn];
bool cmp(int const &x, int const &y) {
	if(lpos[query[x].l] != lpos[query[y].l])
		return lpos[query[x].l] < lpos[query[y].l];
	return query[x].r < query[y].r;
}
void dfs(int dep, int val, int sgn) {
	if(dep == cnt) {
		a[idx][sz[idx]++] = std::make_pair(val, sgn);
	} else {
		dfs(dep + 1, val, sgn);
		dfs(dep + 1, val * pp[dep], -sgn);
	}
}
inline void chg(int x, int v) {
	if(x) {
		bool zero = !s[x];
		s[x] += v;
		if(zero && s[x]) {
			que[qtot] = x;
			pos[x] = qtot++;
		} else if(!zero && !s[x]) {
			pos[x] = -1;
		}
	}
}
inline void upd(int x, int v) {
	for(int i = 0; i < sz[x]; ++i) {
		int pos = a[x][i].first, dt = a[x][i].second;
		chg(c[pos], -dt);
		chg(c[pos] += v, dt);
	}
}
int main() {
	for(int i = 2; i < maxm; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxm; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	fact[0] = iact[0] = 1;
	for(int i = 1; i < maxn; ++i) {
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	while(scanf("%d", &n) == 1) {
		sqn = 361; // for(sqn = 1; sqn * sqn < n; ++sqn);
		int mx = 0;
		for(int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			mx = std::max(mx, x);
			for(cnt = 0; x > 1; ++cnt)
				for(pp[cnt] = d[x], x /= pp[cnt]; d[x] == pp[cnt]; x /= pp[cnt]);
			idx = i;
			sz[i] = 0;
			dfs(0, 1, 1);
			lpos[i] = i <= sqn ? 1 : lpos[i - sqn] + 1;
		}
		scanf("%d", &q);
		for(int i = 1; i <= q; ++i) {
			scanf("%d%d%d", &query[i].l, &query[i].r, &query[i].k);
			ord[i] = i;
		}
		std::sort(ord + 1, ord + q + 1, cmp);
		memset(c + 1, 0, mx * sizeof(int));
		memset(s + 1, 0, n * sizeof(int));
		memset(pos + 1, -1, n * sizeof(int));
		qtot = 0;
		for(int i = 1, pL = 1, pR = 0; i <= q; ++i) {
			int o = ord[i], m = query[o].k;
			for( ; pL > query[o].l; upd(--pL, 1));
			for( ; pR < query[o].r; upd(++pR, 1));
			for( ; pR > query[o].r; upd(pR--, -1));
			for( ; pL < query[o].l; upd(pL++, -1));
			ans[o] = 0;
			int size = 0;
			for(int j = 0; j < qtot; ++j)
				if(pos[que[j]] == j) {
					int v = que[j];
					if(v >= m)
						ans[o] = (ans[o] + (LL)s[v] * fact[v] % mod * iact[v - m]) % mod;
					que[size] = v;
					pos[v] = size++;
				}
			qtot = size;
			ans[o] = (LL)(ans[o] + mod) * iact[m] % mod;
		}
		for(int i = 1; i <= q; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
