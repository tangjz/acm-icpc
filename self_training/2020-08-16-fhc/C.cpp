#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1;
int n, p[maxn], sz[maxn], up[maxn], cnt[maxn];
int m, in[maxn], out[maxn], seq[maxn];
char typ[maxn + 2];
vector<int> e[maxn];
struct Info {
	LL sum;
	pair<int, int> f[2];
	pair<LL, pair<int, int> > get() const {
		return make_pair(sum, f[0].second > 0 ? f[0] : make_pair(0, 0));
	}
	void check() const {
		assert(f[0].first >= 0 && f[1].first >= 0);
		assert(f[0].second >= 0 && f[1].second >= 0);
		if(!f[0].second)
			assert(!f[0].first);
		if(f[1].second > 0) {
			assert(f[0].second > 0);
			assert(f[0].first > f[1].first);
		} else {
			assert(!f[1].first);
		}
	}
	void add(Info const &t) {
		sum += t.sum;
		for(int i = 0, j = 0; i < 2; ++i) {
			if(!t.f[i].second)
				break;
			for( ; j < 2 && f[j].second > 0 && f[j].first > t.f[i].first; ++j);
			if(j == 2)
				break;
			if(t.f[i].first == f[j].first) {
				f[j].second += t.f[i].second;
			} else {
				for(int k = 1; k > j; --k)
					f[k] = f[k - 1];
				f[j] = t.f[i];
			}
		}
		check();
	}
	void add(int x) {
		sum += x * (x - 1LL) / 2;
		if(!f[0].second || x > f[0].first) {
			f[1] = f[0];
			f[0] = {x, 1};
		} else if(x == f[0].first) {
			++f[0].second;
		} else if(!f[1].second || x > f[1].first) {
			f[1] = {x, 1};
		} else if(x == f[1].first) {
			++f[1].second;
		}
		check();
	}
	void sub(int x) {
		sum -= x * (x - 1LL) / 2;
		if(f[0].second > 0 && x == f[0].first) {
			--f[0].second;
			if(!f[0].second) {
				f[0] = f[1];
				f[1] = {};
			}
		} else if(f[1].second > 0 && x == f[1].first) {
			--f[1].second;
			if(!f[1].second)
				f[1] = {};
		}
		check();
	}
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_build(int L, int R) {
	int rt = seg_idx(L, R);
	if(L < R) {
		int M = (L + R) >> 1;
		seg_build(L, M);
		seg_build(M + 1, R);
		seg[rt] = seg[seg_idx(L, M)];
		seg[rt].add(seg[seg_idx(M + 1, R)]);
	} else {
		seg[rt] = {};
		seg[rt].add(cnt[seq[L]]);
	}
}
Info seg_que(int L, int R, int l, int r) {
	if(l <= L && R <= r)
		return seg[seg_idx(L, R)];
	int M = (L + R) >> 1;
	Info ret = {};
	if(l <= M)
		ret.add(seg_que(L, M, l, r));
	if(r > M)
		ret.add(seg_que(M + 1, R, l, r));
	return ret;
}
void dfs(int u) {
	in[u] = m + 1;
	if(typ[u] == '*' && typ[p[u]] == '*') {
		up[u] = up[p[u]];
	} else {
		up[u] = u;
		seq[++m] = u;
	}
	sz[u] = 1;
	cnt[u] = typ[u] == '*';
	for(int v : e[u]) {
		dfs(v);
		sz[u] += sz[v];
		if(up[v] != v)
			cnt[u] += cnt[v];
	}
	out[u] = m;
}
pair<LL, LL> solve() {
	typ[0] = '\0';
	p[1] = 0;
	for(int i = 2; i <= n; ++i)
		e[p[i]].push_back(i);
	m = 0;
	dfs(1);
	seg_build(1, m);
	LL ans = 0, ways = 0;
	for(int i = 2; i <= n; ++i) {
		Info u = {}, v = {};
		if(in[i] <= out[i]) {
			u = seg_que(1, m, in[i], out[i]);
			if(in[i] > 1)
				v.add(seg_que(1, m, 1, in[i] - 1));
			if(out[i] < m)
				v.add(seg_que(1, m, out[i] + 1, m));
		} else {
			v = seg_que(1, m, 1, m);
		}
		if(typ[i] == '*' && typ[p[i]] == '*') {
			u.add(cnt[i]);
			v.sub(cnt[up[i]]);
			v.add(cnt[up[i]] - cnt[i]);
		}
		pair<int, int> tp;
		int ux, uc, vx, vc;
		LL us, vs;
		tie(us, tp) = u.get();
		tie(ux, uc) = tp;
		tie(vs, tp) = v.get();
		tie(vx, vc) = tp;
		assert(uc > 0 && vc > 0);
		LL tmp = us + vs, adt;
		if(ux > 0 && vx > 0) {
			tmp -= ux * (ux - 1LL) / 2;
			tmp -= vx * (vx - 1LL) / 2;
			int all = ux + vx;
			tmp += all * (all - 1LL) / 2;
			adt = (LL)uc * vc * ux * vx;
		} else {
			adt = (LL)sz[i] * (n - sz[i]);
		}
		if(ans < tmp) {
			ans = tmp;
			ways = 0;
		}
		if(ans == tmp)
			ways += adt;
	}
	for(int i = 1; i <= n; ++i)
		vector<int>().swap(e[i]);
	return {ans, ways};
}
int main() {
	int size = 512 << 20; // 512MB
	char *ptr = (char*)malloc(size) + size;  
	__asm__("movq %0, %%rsp\n" :: "r"(ptr));

	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int K, A, B, C;
		scanf("%d%d%s", &n, &K, typ + 1);
		for(int i = 2; i <= K + 1; ++i)
			scanf("%d", p + i);
		scanf("%d%d%d", &A, &B, &C);
		for(int i = K + 2; i <= n; ++i)
			p[i] = ((LL)A * p[i - 2] + (LL)B * p[i - 1] + C) % (i - 1) + 1;
		pair<LL, LL> ans = solve();
		printf("Case #%d: %lld %lld\n", Case, ans.first, ans.second);
	}

	exit(0);
	// return 0;
}
