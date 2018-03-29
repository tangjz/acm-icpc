#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
struct Fraction {
	int fz, fm;
	bool operator == (Fraction const &t) const {
		return (LL)fz * t.fm == (LL)t.fz * fm;
	}
	bool operator < (Fraction const &t) const {
		return (LL)fz * t.fm < (LL)t.fz * fm;
	}
} seq[maxn];
int n, m, bit[maxn];
pair<Fraction, Fraction> seg[maxn];
void bit_add(int x, int v) {
	for( ; x <= m; x += x & -x)
		bit[x] += v;
}
int bit_sum(int x) {
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		int x, v;
		scanf("%d%d", &x, &v);
		if(v < 0) {
			seg[i] = make_pair((Fraction){x, -v + m}, (Fraction){-x, -v - m});
		} else {
			seg[i] = make_pair((Fraction){-x, v - m}, (Fraction){x, v + m});
		}
		seq[i] = seg[i].second;
	}
	sort(seg, seg + n);
	sort(seq, seq + n);
	m = unique(seq, seq + n) - seq;
	LL ans = 0;
	for(int i = 0; i < n; ++i) {
		int idx = lower_bound(seq, seq + m, seg[i].second) - seq + 1;
		ans += bit_sum(idx);
		bit_add(idx, 1);
	}
	printf("%lld\n", ans);
	return 0;
}
