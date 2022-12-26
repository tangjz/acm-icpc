#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e3 + 9, INF = 0x3f3f3f3f;
int n, m, xtot, xque[maxn], ytot, yque[maxn];
struct Line {
	int L, R, pos;
	void read() {
		scanf("%d%d%d", &L, &R, &pos);
	}
} er[maxn], ec[maxn];
bool vis[maxn][maxn], banL[maxn][maxn], banR[maxn][maxn], banU[maxn][maxn], banD[maxn][maxn];
int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		scanf("%d%d", &n, &m);
		xtot = ytot = 0;
		xque[xtot++] = yque[ytot++] = -INF;
		xque[xtot++] = yque[ytot++] = INF;
		for(int i = 0; i < n; ++i) {
			Line &cur = er[i];
			cur.read(); // xL xR y
			xque[xtot++] = cur.L;
			xque[xtot++] = cur.R;
			yque[ytot++] = cur.pos;
		}
		for(int i = 0; i < m; ++i) {
			Line &cur = ec[i];
			cur.read(); // x yL yR
			swap(cur.pos, cur.L); // yR yL x
			swap(cur.L, cur.R); // yL yR x
			yque[ytot++] = cur.L;
			yque[ytot++] = cur.R;
			xque[xtot++] = cur.pos;
		}
		sort(xque, xque + xtot);
		xtot = unique(xque, xque + xtot) - xque;
		sort(yque, yque + ytot);
		ytot = unique(yque, yque + ytot) - yque;
		for(int i = 0; i < xtot - 1; ++i)
			for(int j = 0; j < ytot - 1; ++j) {
				vis[i][j] = 0;
				banL[i][j] = j == 0;
				banR[i][j] = j == ytot - 2;
				banU[i][j] = i == 0;
				banD[i][j] = i == xtot - 2;
			}
		for(int i = 0; i < n; ++i) {
			Line &cur = er[i];
			int xL = lower_bound(xque, xque + xtot, cur.L) - xque;
			int xR = lower_bound(xque, xque + xtot, cur.R) - xque;
			int y = lower_bound(yque, yque + ytot, cur.pos) - yque;
			for(int x = xL; x < xR; ++x) {
				banL[x][y] = 1;
				banR[x][y - 1] = 1;
			}
//			printf("ban [%d, %d) x %d\n", xL, xR, y);
//			show();
		}
		for(int i = 0; i < m; ++i) {
			Line &cur = ec[i];
			int yL = lower_bound(yque, yque + ytot, cur.L) - yque;
			int yR = lower_bound(yque, yque + ytot, cur.R) - yque;
			int x = lower_bound(xque, xque + xtot, cur.pos) - xque;
			for(int y = yL; y < yR; ++y) {
				banU[x][y] = 1;
				banD[x - 1][y] = 1;
			}
//			printf("ban %d x [%d, %d)\n", x, yL, yR);
//			show();
		}
		int sx = lower_bound(xque, xque + xtot, 0) - xque - 1;
		int sy = lower_bound(yque, yque + ytot, 0) - yque - 1;
		LL ans = 0;
		bool inf = 0;
		int tot = 0;
		static pair<int, int> que[maxn * maxn];
		auto append = [&](int x, int y) {
			if(x < 0 || x >= xtot - 1 || y < 0 || y >= ytot - 1 || vis[x][y])
				return;
			vis[x][y] = 1;
			inf |= x == 0 || x == xtot - 2 || y == 0 || y == ytot - 2;
			ans += (LL)(xque[x + 1] - xque[x]) * (yque[y + 1] - yque[y]);
			que[tot++] = make_pair(x, y);
		};
		append(sx, sy);
		for(int i = 0; !inf && i < tot; ++i) {
			int x, y;
			tie(x, y) = que[i];
			if(!banL[x][y])
				append(x, y - 1);
			if(!banR[x][y])
				append(x, y + 1);
			if(!banU[x][y])
				append(x - 1, y);
			if(!banD[x][y])
				append(x + 1, y);
		}
		if(inf) {
			puts("INF");
		} else {
			printf("%lld\n", ans);
		}
//		printf("%d %d\n", sx, sy);
//		show();
	}
	return 0;
}