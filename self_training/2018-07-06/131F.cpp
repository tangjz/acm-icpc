#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e4 + 1;
int n, m, q, base, ord[maxn], idx[maxn], cnt[maxn], lpos[maxn];
LL res[maxn];
char buf[maxn];
struct Mask {
	LL data[3];
	int get(int pos) const {
		return (data[pos / 9] >> (pos % 9 * 6)) & 63;
	}
	void add(int pos) {
		int pre = get(pos), cur = (pre + 1) % base;
		data[pos / 9] ^= (LL)(pre ^ cur) << (pos % 9 * 6);
	}
	bool operator < (Mask const &t) const {
		for(int i = 0; i < 3; ++i)
			if(data[i] != t.data[i])
				return data[i] < t.data[i];
		return 0;
	}
} msk[maxn];
struct Query {
	int idx, L, R;
	void read(int id) {
		idx = id;
		scanf("%d%d", &L, &R);
		--L;
	}
	bool operator < (Query const &t) const {
		if(lpos[L] != lpos[t.L])
			return lpos[L] < lpos[t.L];
		return R < t.R;
	}
} que[maxn];
int main() {
	scanf("%d%s%d", &base, buf + 1, &q);
	for(int i = 1; i <= q; ++i)
		que[i].read(i);
	n = strlen(buf + 1);
	for(int i = 1; i <= n; ++i) {
		msk[i] = msk[i - 1];
		msk[i].add(buf[i] - 'a');
		ord[i] = i;
	}
	sort(ord, ord + n + 1, [&](int const &u, int const &v) {
		return msk[u] < msk[v];
	});
	m = 0;
	for(int i = 0; i <= n; ++i)
		idx[ord[i]] = !i || msk[ord[i - 1]] < msk[ord[i]] ? ++m : m;
	int sq = (int)ceil(sqrt(q));
	for(int i = 1; i <= n; ++i)
		lpos[i] = i < sq ? 0 : lpos[i - sq] + 1;
	sort(que + 1, que + q + 1);
	int qL = 0, qR = -1;
	LL ans = 0;
	for(int i = 1; i <= q; ++i) {
		for( ; qL > que[i].L; --qL)
			ans += cnt[idx[qL - 1]]++;
		for( ; qR < que[i].R; ++qR)
			ans += cnt[idx[qR + 1]]++;
		for( ; qL < que[i].L; ++qL)
			ans -= --cnt[idx[qL]];
		for( ; qR > que[i].R; --qR)
			ans -= --cnt[idx[qR]];
		res[que[i].idx] = ans;
	}
	for(int i = 1; i <= q; ++i)
		printf("%lld\n", res[i]);
	return 0;
}
