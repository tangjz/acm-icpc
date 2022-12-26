#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e3 + 1, maxm = (int)1e6 + 1;

void solve() {
	int r, c, n = 0, m = 0;
	static int cand[2][maxn << 1 | 1], cur = 0, pre = 1;
	static char buf[maxn][maxn], ans[maxn << 1 | 1];
	scanf("%d%d", &r, &c);
	for(int i = 0; i < r; ++i)
		scanf("%s", buf[i]);
	if(buf[0][0] == '0') {
		int L = 0, R = 0;
		static int que[maxm];
		buf[0][0] = ' ';
		que[R++] = 0;
		while(L < R) {
			int u = que[L++], ux = u / c, uy = u % c;
			n = max(n, ux + uy);
			for(int dx = -1; dx <= 1; ++dx)
				for(int dy = -1; dy <= 1; ++dy) {
					if(!dx == !dy)
						continue;
					int vx = ux + dx, vy = uy + dy;
					if(vx < 0 || vx >= r || vy < 0 || vy >= c || buf[vx][vy] != '0')
						continue;
					buf[vx][vy] = ' ';
					que[R++] = u + dx * c + dy;
				}
		}
		cand[cur][0] = 0;
		for(int i = 0; i < r; ++i) {
			int j = n - i;
			if(j >= 0 && j < c && buf[i][j] == ' ')
				cand[cur][++cand[cur][0]] = i;
		}
	} else {
		buf[0][0] = ' ';
		cand[cur][0] = 0;
		cand[cur][++cand[cur][0]] = 0;
		ans[m++] = '1';
	}
	for( ; n < r + c - 2; ++n) {
		swap(cur, pre);
		char best = '1', ch;
		cand[cur][0] = 0;
		for(int i = 1; i <= cand[pre][0]; ++i) {
			int x = cand[pre][i], y = n - x;
			if(x + 1 < r && (ch = buf[x + 1][y]) != ' ') {
				if(ch < best) {
					best = ch;
					cand[cur][0] = 0;
				}
				if(ch == best)
					cand[cur][++cand[cur][0]] = x + 1;
				buf[x + 1][y] = ' ';
			}
			if(y + 1 < c && (ch = buf[x][y + 1]) != ' ') {
				if(ch < best) {
					best = ch;
					cand[cur][0] = 0;
				}
				if(ch == best)
					cand[cur][++cand[cur][0]] = x;
				buf[x][y + 1] = ' ';
			}
		}
		ans[m++] = best;
	}
	if(!m)
		ans[m++] = '0';
	ans[m] = '\0';
	puts(ans);
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1, n; Case <= T; ++Case) {
        // printf("Case #%d: ", Case);
        solve();
    }
    return 0;
}
