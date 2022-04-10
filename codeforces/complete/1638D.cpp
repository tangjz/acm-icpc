#include <bits/stdc++.h>
using namespace std;

typedef signed i32;
typedef unsigned u32;
typedef long long i64;
typedef unsigned long long u64;
// typedef __int128_t i128;
// typedef __uint128_t u128;
typedef float f32;
typedef double f64;
typedef long double f128;

const int maxn = (int)1e6 + 1, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n, m;
    scanf("%d%d", &n, &m);
	int tot = 0;
	static int mat[maxn], seq[maxn][5], stk[maxn];
	static bool vis[maxn];
	for(int i = 0, idx = 0; i < n; ++i)
		for(int j = 0; j < m; ++j, ++idx) {
			scanf("%d", mat + idx);
			seq[idx][0] = 0;
			vis[idx] = 0;
			for(int dx = 0, tmp = idx; dx < 2 && dx <= i; ++dx, tmp -= m)
				for(int dy = 0, nid = tmp; dy < 2 && dy <= j; ++dy, --nid)
					seq[nid][++seq[nid][0]] = mat[idx];
		}
	for(int i = 0, idx = 0; i < n; ++i)
		for(int j = 0; j < m; ++j, ++idx) {
			if(i == n - 1 || j == m - 1)
				continue;
			sort(seq[idx] + 1, seq[idx] + seq[idx][0] + 1);
			if(!vis[idx] && (!seq[idx][0] || seq[idx][1] == seq[idx][seq[idx][0]])) {
				vis[idx] = 1;
				stk[tot++] = idx;
			}
		}
	auto upd = [&](int uid, int ux, int uy) {
		int &val = mat[uid];
		if(val == -1)
			return;
		for(int dx = 0, vx = ux, tmp = uid; dx < 2 && dx <= ux; ++dx, --vx, tmp -= m)
			for(int dy = 0, vy = uy, vid = tmp; dy < 2 && dy <= uy; ++dy, --vy, --vid) {
				if(vx == n - 1 || vy == m - 1)
					continue;
				for(int i = seq[vid][0]; i > 0; --i)
					if(seq[vid][i] == val) {
						for(int j = i; j < seq[vid][0]; ++j)
							seq[vid][j] = seq[vid][j + 1];
						--seq[vid][0];
						break;
					}
				if(!vis[vid] && (!seq[vid][0] || seq[vid][1] == seq[vid][seq[vid][0]])) {
					vis[vid] = 1;
					stk[tot++] = vid;
				}
			}
		val = -1;
	} ;
	int q = 0;
	static int out[maxn][3];
	while(tot > 0) {
		int uid = stk[--tot], ux = uid / m, uy = uid % m;
		if(seq[uid][0]) {
			out[q][0] = ux;
			out[q][1] = uy;
			out[q++][2] = seq[uid][1];
		}
		for(int dx = 0, vx = ux, tmp = uid; dx < 2; ++dx, ++vx, tmp += m)
			for(int dy = 0, vy = uy, vid = tmp; dy < 2; ++dy, ++vy, ++vid)
				upd(vid, vx, vy);
	}
	bool chk = 1;
	for(int i = 0, idx = 0; chk && i < n; ++i)
		for(int j = 0; chk && j < m; ++j, ++idx)
			chk &= mat[idx] == -1;
	if(!chk) {
		puts("-1");
		return;
	}
	printf("%d\n", q);
	for(int i = q - 1; i >= 0; --i)
		printf("%d %d %d\n", out[i][0] + 1, out[i][1] + 1, out[i][2]);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		// printf("%d\n", solve());
		solve();
	}
	return 0;
}