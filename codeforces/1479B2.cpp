#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;
 
const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)1e5 + 9, maxm = (int)2e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);
 
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
 
const int INIT_VALUE = INT_MAX;
int seg[maxn << 1 | 1];
inline int segIdx(int L, int R) {
	return (L + R) | (L < R);
}
inline void segInit(int L, int R) {
	int rt = segIdx(L, R);
	seg[rt] = INIT_VALUE;
	if(L < R) {
		int M = (L + R) >> 1;
		segInit(L, M);
		segInit(M + 1, R);
	}
}
inline void segUpd(int L, int R, int x, int v) {
	int rt = segIdx(L, R);
	if(L == R) {
		seg[rt] = v;
	} else {
		int M = (L + R) >> 1;
		if(x <= M) {
			segUpd(L, M, x, v);
		} else {
			segUpd(M + 1, R, x, v);
		}
		int lch = segIdx(L, M);
		int rch = segIdx(M + 1, R);
		seg[rt] = min(seg[lch], seg[rch]);
	}
}
inline int segQue(int L, int R, int l, int r) {
	if(l <= L && R <= r) {
		int rt = segIdx(L, R);
		return seg[rt];
	}
	int M = (L + R) >> 1;
	int ret = INIT_VALUE;
	if(l <= M)
		ret = min(ret, segQue(L, M, l, r));
	if(r > M)
		ret = min(ret, segQue(M + 1, R, l, r));
	return ret;
}
 
void solve() {
	int n, m;
	static int a[maxn], que[maxn];
	scanf("%d", &n);
	m = a[0] = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		que[m++] = a[i];
	}
	que[m++] = 0;
	sort(que, que + m);
	m = unique(que, que + m) - que;
	segInit(0, m - 1);
	int sum = 0;
	a[0] = lower_bound(que, que + m, a[0]) - que;
	for(int i = 1; i <= n; ++i) {
		a[i] = lower_bound(que, que + m, a[i]) - que;
		if(i == 1) {
			segUpd(0, m - 1, a[0], 1);
			continue;
		}
		int adt = a[i] != a[i - 1];
		int val = INIT_VALUE;
		if(a[i] > 0)
			val = min(val, segQue(0, m - 1, 0, a[i] - 1));
		if(a[i] < m - 1)
			val = min(val, segQue(0, m - 1, a[i] + 1, m - 1));
		if(val != INIT_VALUE)
			++val;
		val = min(val, segQue(0, m - 1, a[i], a[i]));
		segUpd(0, m - 1, a[i - 1], val - adt);
		sum += adt;
		// for(int j = 0; j < m; ++j)
		// 	printf("dp(%d, %d)=%d\n", i, j, sum + segQue(0, m - 1, j, j));
	}
	printf("%d\n", segQue(0, m - 1, 0, m - 1) + sum);
}
 
int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}