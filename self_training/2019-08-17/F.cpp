#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxs = 3 * maxn;
int n, m;
pair<int, int> a[maxn];
struct Coordinates {
	int tot, que[maxs], pR[maxs];
	vector<int> pos[maxs];
	void build() {
		sort(que, que + tot);
		tot = unique(que, que + tot) - que;
		memset(pR, 0x3f, tot * sizeof(int));
		for(int i = 0, j = 0; i < tot; ++i) {
			for( ; j < i && que[i] - que[j] > m; ++j);
			if(j < i && que[i] - que[j] == m)
				pR[j] = i;
		}
	}
	void add(int x) {
		que[tot++] = x;
	}
	void add(int x, int id) {
		pos[query(x)].push_back(id);
	}
	int query(int x) {
		return lower_bound(que, que + tot, x) - que;
	}
} X, Y;
struct MaxSet {
	int tot, seq[maxs], mx, ctr[maxn];	
	void build() {
		ctr[mx = 0] = 0;
		for(int i = 0; i < tot; ++i) {
			for( ; mx < seq[i]; ctr[++mx] = 0);
			++ctr[seq[i]];
		}
	}
	void add(int x) {
		--ctr[seq[x]];
		++seq[x];
		if(mx < seq[x])
			ctr[++mx] = 0;
		++ctr[seq[x]];
	}
	void sub(int x) {
		--ctr[seq[x]];
		--seq[x];
		if(mx && !ctr[mx])
			--mx;
		++ctr[seq[x]];
	}
} F;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%d%d", &a[i].first, &a[i].second);
		for(int j = 0; j < 3; ++j) {
			X.add(a[i].first - j * m);
			Y.add(a[i].second - j * m);
		}
	}
	X.build();
	Y.build();
	for(int i = 0; i < n; ++i) {
		X.add(a[i].first, i);
		Y.add(a[i].second, i);
	}
	F.tot = Y.tot;
	for(int i = 0; i < Y.tot; ++i) {
		F.seq[i] = 0;
		for(int j = 0, k = i; j < 3 && k < Y.tot; ++j, k = Y.pR[k])
			F.seq[i] += (int)Y.pos[k].size();
	}
	F.build();
	int ans = F.mx;
	for(int i = 0; i < X.tot; ++i) {
		int adt = 0;
		for(int j = 0, k = i; j < 3 && k < X.tot; ++j, k = X.pR[k])
			for(int id : X.pos[k]) {
				int u = Y.query(a[id].second - m - m);
				for(int o = 0; o < 3; ++o, u = Y.pR[u])
					F.sub(u);
				++adt;
			}
		ans = max(ans, adt + F.mx);
		for(int j = 0, k = i; j < 3 && k < X.tot; ++j, k = X.pR[k])
			for(int id : X.pos[k]) {
				int u = Y.query(a[id].second - m - m);
				for(int o = 0; o < 3; ++o, u = Y.pR[u])
					F.add(u);
			}
	}
	printf("%d\n", ans);
	return 0;
}