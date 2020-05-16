#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e4 + 1, INF = 0x3f3f3f3f;

typedef pair<int, int> Point;
typedef vector<Point> Segment;
Segment sL[maxn << 1 | 1], sR[maxn << 1 | 1];
inline LL det(Point p, Point q, Point r) {
	int x1 = q.first - p.first;
	int y1 = q.second - p.second;
	int x2 = r.first - q.first;
	int y2 = r.second - q.second;
	return (LL)x1 * y2 - (LL)x2 * y1;
}
void seg_upd(Segment &vec, Point p) { // in increasing order of p.first
	int sz = vec.size();
	while(sz > 1 && det(vec[sz - 2], vec.back(), p) <= 0) {
		vec.pop_back();
		--sz;
	}
	if(sz > 0 && vec.back().first == p.first)
		vec.back() = min(vec.back(), p);
	else
		vec.push_back(p);
}
inline int calc(Point p, int v) {
	return p.first * v + p.second;
}
int seg_que(Segment &vec, int v) { // in increasing order of v
	int sz = vec.size();
	if(!sz)
		return INF;
	int ret = calc(vec.back(), v), tmp;
	while(sz > 1 && (tmp = calc(vec[sz - 2], v)) < ret) {
		vec.pop_back();
		--sz;
		ret = tmp;
	}
	return min(ret, INF);
}
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_upd(int L, int R, int x, Point p) {
	seg_upd(sL[seg_idx(L, R)], p);
	if(L < R) {
		int M = (L + R) >> 1;
		if(x <= M)
			seg_upd(L, M, x, p);
		else
			seg_upd(M + 1, R, x, p);
	}
}
int seg_que(int L, int R, int l, int r, int v) {
	if(l <= L && R <= r)
		return seg_que(sL[seg_idx(L, R)], v);
	int M = (L + R) >> 1, ret = INF;
	if(l <= M)
		ret = min(ret, seg_que(L, M, l, r, v));
	if(r > M)
		ret = min(ret, seg_que(M + 1, R, l, r, v));
	return ret;
}
void seg_upd(int L, int R, int l, int r, Point p) {
	if(l <= L && R <= r) {
		seg_upd(sR[seg_idx(L, R)], p);
		return;
	}
	int M = (L + R) >> 1;
	if(l <= M)
		seg_upd(L, M, l, r, p);
	if(r > M)
		seg_upd(M + 1, R, l, r, p);
}
int seg_que(int L, int R, int x, int v) {
	int ret = seg_que(sR[seg_idx(L, R)], v);
	if(L < R) {
		int M = (L + R) >> 1;
		if(x <= M)
			ret = min(ret, seg_que(L, M, x, v));
		else
			ret = min(ret, seg_que(M + 1, R, x, v));
	}
	return ret;
}

int n, m, a[maxn + 2], tot, stk[maxn];
int pL[maxn], pR[maxn], ord[maxn];
int f[2][maxn], cur, pre = 1;
int main() {
	scanf("%d%d", &n, &m);
	a[0] = a[n + 1] = INF;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		for(pL[i] = i; a[pL[i] - 1] < a[i]; pL[i] = pL[pL[i] - 1]);
		ord[i] = i;
	}
	for(int i = n; i >= 1; --i)
		for(pR[i] = i; a[pR[i] + 1] <= a[i]; pR[i] = pR[pR[i] + 1]);
	sort(ord + 1, ord + n + 1, [&](int u, int v) {
		return a[u] < a[v];
	});
	for(int i = 0; i <= n; ++i)
		f[cur][i] = i ? INF : 0;
	for(int i = 1; i <= m; ++i) {
		swap(cur, pre);
		for(int j = seg_idx(1, 1), k = seg_idx(n, n); j <= k; ++j) {
			Segment().swap(sL[j]);
			Segment().swap(sR[j]);
		}
		for(int j = n - 1; j >= 0; --j)
			seg_upd(1, n, j + 1, (Point){-j, f[pre][j]}); // sL
		for(int o = 1; o <= n; ++o) {
			int j = ord[o];
			int cost = seg_que(1, n, pL[j], j, a[j]); // sL
			seg_upd(1, n, j, pR[j], (Point){a[j], cost}); // sR
		}
		f[cur][0] = INF;
		for(int j = 1; j <= n; ++j)
			f[cur][j] = seg_que(1, n, j, j); // sR
	}
	printf("%d\n", f[cur][n]);
	return 0;
}
