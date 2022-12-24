#include <bits/stdc++.h>
using namespace std;
const int maxn = 6, maxm = 100, maxd = 1 << maxn, maxs = 3762;
int n, m, tot, all, w[maxs + 1], go[maxd + 1][maxs + 1];
void init() {
	typedef unsigned long long ULL;
	set<pair<ULL, int> > Hash;
	ULL que[maxs + 1], adt[maxn + 1];
	que[tot++] = 1ULL << 0;
	Hash.insert(make_pair(que[tot - 1], tot - 1));
	for(int cid = 0; cid < tot; ++cid) {
		ULL msk = que[cid];
		for(int i = 0; i < n; ++i) {
			adt[i] = msk;
			for(int j = 0; j < all; ++j)
				if((msk >> j) & 1)
					adt[i] |= 1ULL << (j | (1 << i));
		}
		w[cid] = 0;
		for(int i = 0; i < all; ++i) {
			if((msk >> i) & 1) {
				int cnt = 0;
				for(int j = 0; j < n; ++j)
					cnt += (i >> j) & 1;
				w[cid] = max(w[cid], cnt);
			}
			ULL nmsk = msk;
			for(int j = 0; j < n; ++j)
				if((i >> j) & 1)
					nmsk |= adt[j];
			int nid;
			set<pair<ULL, int> >::const_iterator it = Hash.lower_bound(make_pair(nmsk, 0));
			if(it == Hash.end() || it -> first != nmsk) {
				que[nid = tot++] = nmsk;
				Hash.insert(make_pair(que[tot - 1], tot - 1));
			} else {
				nid = it -> second;
			}
			go[i][cid] = nid;
		}
	}
}
double mat[maxm + 1][maxn + 1], f[2][maxs + 1];
int main() {
	scanf("%d%d", &n, &m);
	all = 1 << n;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			scanf("%lf", mat[j] + i);
	init();
	int cur = 0, pre = 1;
	for(int i = 0; i < tot; ++i)
		f[cur][i] = !i;
	for(int i = 0; i < m; ++i) {
		double *vec = mat[i];
		swap(cur, pre);
		for(int j = 0; j < tot; ++j)
			f[cur][j] = 0;
		for(int j = 0; j < all; ++j) {
			double prd = 1;
			for(int k = 0; k < n; ++k)
				prd *= (j >> k) & 1 ? vec[k] : 1 - vec[k];
			for(int k = 0; k < tot; ++k)
				f[cur][go[j][k]] += prd * f[pre][k];
		}
	}
	double ans = 0;
	for(int i = 0; i < tot; ++i)
		ans += w[i] * f[cur][i];
	printf("%.2f\n", ans);
	return 0;
}
