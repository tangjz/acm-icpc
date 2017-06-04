#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef long double DB;
const int maxn = 251, maxm = 10001;
const LL INF = (LL)2e18;
const DB eps = 1e-10;
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
inline int dcmp(DB x, DB y) {
	return sgn(x - y);
}
int n, m, cur, pre = 1;
LL f[2][maxm];
struct CNode {
	int v, dv;
	bool operator < (CNode const &t) const {
		return v > t.v;
	}
} a[maxn];
void solve(int L, int R, int dL, int dR, int c, int v, int dv) {
	if(L > R)
		return;
	int M = L + ((R - L) >> 1) / c * c, dM = M;
	for(int i = dL; i <= dR && i <= M; i += c) {
		if(f[pre][i] == -INF)
			continue;
		int diff = (M - i) / c;
		LL val = f[pre][i] + diff * v - ((diff * (diff - 1LL)) >> 1) * dv;
		if(f[cur][M] < val) {
			dM = i;
			f[cur][M] = val;
		}
	}
	solve(L, M - c, dL, dM, c, v, dv);
	solve(M + c, R, dM, dR, c, v, dv);
}
int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		for(int i = 1; i <= m; ++i)
			f[cur][i] = -INF;
		int tp = n;
		n = 0;
		while(tp--) {
			char op[2];
			int c, v, dv;
			scanf("%s", op);
			if(op[0] == 'D') {
				scanf("%d%d%d", &c, &v, &dv);
				pre ^= 1;
				cur ^= 1;
				for(int i = 1; i <= m; ++i)
					f[cur][i] = -INF;
				for(int r = 0; r < c && r <= m; ++r) {
					int L = r, R = (m - r) / c * c + r;
					solve(L, R, L, R, c, v, dv);
				}
				//~ for(int i = 0; i <= m; ++i)
					//~ printf("%lld%c", f[cur][i], " \n"[i == m]);
			} else { // 'C'
				scanf("%d%d", &v, &dv);
				a[n++] = (CNode){v, dv};
			}
		}
		sort(a, a + n);
		int chk = 0;
		DB rat = 0, lt = 0, sum = 0, ans = f[cur][m];
		for(int i = 0, j = 0; i < n; i = j) {
			int lv = a[i].v;
			for( ; j < n && a[j].v == lv; ++j)
				if(!chk)
					a[j].dv ? (rat += 1.0 / a[j].dv) : (chk = 1);
			//~ printf("rat: %f\n", rat);
			//~ printf("%d -> %d : %f -> ? : %f\n", lv, j < n ? a[j].v : -1, lt, chk ? 0 : 1 / rat);
			if(chk) {
				for(int k = 0; k <= m; ++k)
					if(dcmp(k, lt) >= 0) {
						DB val = f[cur][m - k] + sum + (k - lt) * lv;
						if(ans < val)
							ans = val;
					}
				break;
			} // else chk == 0
			for(int k = 0; k <= m; ++k)
				if(dcmp(k, lt) >= 0) {
					DB dt = k - lt, v = lv - dt / rat;
					DB val = f[cur][m - k] + sum + (lv + v) * 0.5 * dt;
					if(ans < val)
						ans = val;
				}
			if(j == n)
				continue;
			int rv = a[j].v;
			DB dt = (lv - rv) * rat, rt = lt + dt;
			sum += (lv + rv) * 0.5 * dt;
			lv = rv;
			lt = rt;
		}
		if(dcmp(ans, -INF) > 0)
			printf("%.10f\n", (double)ans);
		else
			puts("impossible");
	}
	return 0;
}
