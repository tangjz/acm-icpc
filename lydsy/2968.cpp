#include <bits/stdc++.h>
using namespace std;
const int maxm = 651, INF = 0x3f3f3f3f;
int n, m, a[2][maxm], f[2][maxm][maxm], ord[maxm], ans[maxm];
void upd_max(int &x, int y) {
	x < y && (x = y);
}
struct Vector {
	int x, y, z;
	void read() {
		scanf("%d%d%d", &y, &x, &z);
	}
} que[maxm];
bool cmp(int const &u, int const &v) {
	Vector const &lft = que[u];
	Vector const &rht = que[v];
	return lft.x * rht.y - lft.y * rht.x < 0;
}
int tot;
struct Point {
	int x, y;
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	int det(Point const &t) const {
		return x * t.y - y * t.x;
	}
} p[maxm];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < n; ++j)
			scanf("%d", a[i] + j);
	for(int i = 0; i < m; ++i) {
		que[i].read();
		ord[i] = i;
		ans[i] = -INF;
	}
	sort(ord, ord + m, cmp);
	int pre = 1, pFL, pFR, pPL, pPR;
	int cur = 0, cFL = 0, cFR = 0, cPL = 0, cPR = 0;
	f[cur][0][0] = 0;
	for(int i = 0; i < n; ++i) {
		const int T = a[0][i], absT = abs(T), T4 = T / 4, T6 = T / 6;
		const int W = a[1][i], absW = abs(W), W3 = W / 3, W6 = W / 6, W9 = W / 9;
		swap(cur, pre);
		pFL = cFL;
		cFL += min(min(-1, W6), min(-1 + W9, 2 + W3));
		pFR = cFR;
		cFR += max(max(-1, W6), max(-1 + W9, 2 + W3));
		pPL = cPL;
		cPL += min(min(-1, -T4), min(3 + T4, -1 + T6));
		pPR = cPR;
		cPR += max(max(-1, -T4), max(3 + T4, -1 + T6));
		for(int i = 0; i <= cFR - cFL; ++i)
			for(int j = 0; j <= cPR - cPL; ++j)
				f[cur][i][j] = -INF;
		for(int i = 0; i <= pFR - pFL; ++i)
			for(int j = 0; j <= pPR - pPL; ++j) {
				int pH = f[pre][i][j];
				if(pH == -INF)
					continue;
				int pF = i + pFL, x = pF - cFL;
				int pP = j + pPL, y = pP - cPL;
				upd_max(f[cur][x - 1][y - 1], pH * 4 / 5 + 3 + pF / 6 + pP / 6);
				upd_max(f[cur][x + W6][y - T4], pH + T - W);
				upd_max(f[cur][x - 1 + W9][y + 3 + T4], pH - absW - pF / 4);
				upd_max(f[cur][x + 2 + W3][y - 1 + T6], pH - absT - pP / 4);
			}
	}
	for(int i = 0; i <= cFR - cFL; ++i) {
		tot = 0;
		for(int j = 0; j <= cPR - cPL; ++j) {
			int cH = f[cur][i][j];
			if(cH == -INF)
				continue;
			Point q = (Point){j + cPL, cH};
			for( ; tot > 1 && (p[tot - 1] - p[tot - 2]).det(q - p[tot - 1]) >= 0; --tot);
			p[tot++] = q;
		}
		if(!tot)
			continue;
		for(int j = 0, k = 0; j < m; ++j) {
			int o = ord[j], val = que[o].x * p[k].x + que[o].y * p[k].y, tmp;
			for( ; k + 1 < tot && (tmp = que[o].x * p[k + 1].x + que[o].y * p[k + 1].y) > val; ++k, val = tmp);
			ans[o] = max(ans[o], val + que[o].z * (i + cFL));
		}
	}
	for(int i = 0; i < m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
