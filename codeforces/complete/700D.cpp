#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 3;
int n, sq, a[maxn], c[maxn], d[maxn], dL[maxn], dR[maxn];
int q, pos[maxn], qL[maxn], qR[maxn], ord[maxn], ans[maxn];
inline void upd(int x, int v) {
	int y = c[x];
	if(!(--d[y])) {
		dL[dR[y]] = dL[y];
		dR[dL[y]] = dR[y];
	}
	int z = c[x] += v;
	if(!(d[z]++)) {
		dL[z] = v > 0 && d[y] ? y : dL[y];
		dR[z] = v < 0 && d[y] ? y : dR[y];
		dL[dR[z]] = z;
		dR[dL[z]] = z;
	}
}
int main() {
	scanf("%d", &n);
	for( ; sq * sq <= n; ++sq);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		pos[i] = pos[max(i - sq, 0)] + 1;
	}
	scanf("%d", &q);
	for(int i = 1; i <= q; ++i) {
		scanf("%d%d", qL + i, qR + i);
		ord[i] = i;
	}
	sort(ord + 1, ord + q + 1, [&](int const &u, int const &v) {
		return pos[qL[u]] != pos[qL[v]] ? (pos[qL[u]] < pos[qL[v]]) : (qR[u] > qR[v]);
	});
	d[0] = d[n + 1] = maxn;
	dL[n + 1] = 0;
	dR[0] = n + 1;
	for(int i = 1, pL = 1, pR = 0; i <= q; ++i) {
		int o = ord[i];
		for( ; pL > qL[o]; upd(a[--pL], 1));
		for( ; pR < qR[o]; upd(a[++pR], 1));
		for( ; pR > qR[o]; upd(a[pR--], -1));
		for( ; pL < qL[o]; upd(a[pL++], -1));
		int &ret = ans[o] = 0;
		queue<pair<int, int> > Q;
		auto append = [&](int v, int c) {
			ret += v * c;
			if(!Q.empty() && Q.back().first == v) {
				Q.back().second += c;
			} else {
				Q.push(make_pair(v, c));
			}
		};
		for(int j = dR[0], las = 0; j <= n || !Q.empty(); ) {
			pair<int, int> cur = Q.empty() ? make_pair(maxn, 0) : Q.front();
			int val = min(j <= n ? j : maxn, cur.first), ctr = 0;
			if(val == j) {
				ctr += d[j];
				j = dR[j];
			}
			if(val == cur.first) {
				ctr += cur.second;
				Q.pop();
			}
			if(las) {
				append(las + val, 1);
				las = 0;
				--ctr;
			}
			if(ctr > 1)
				append(val + val, ctr >> 1);
			if(ctr & 1)
				las = val;
		}
	}
	for(int i = 1; i <= q; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
