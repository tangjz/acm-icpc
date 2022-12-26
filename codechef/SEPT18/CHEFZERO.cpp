#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
const int maxn = (int)1e3 + 1, maxm = (int)1e6 + 1, maxt = 600;
const LL INF = ~0ull >> 1;
int n, m, q, mat[maxn][maxn], pos[maxn][maxn], ord[maxm], seq[maxm], len[maxn];
LL sum[maxm], ans = INF;
void solve(bool rev = 0) {
	int all = n * m, plen = all / q, rem = all % q;
	static int perm[maxm];
	for(int i = 0; i < all; ++i) {
		int x = ord[i] / m, y = ord[i] % m;
		seq[i] = mat[x][y];
		sum[i + 1] = sum[i] + seq[i];
	}
	{ // greedy
		int cur = 0, nxt;
		LL low = INF, upp = 0;
		for(int i = 0; i < q; ++i) {
			LL tmp = 0, rem = sum[all] - sum[cur], avg = rem / (q - i);
			nxt = upper_bound(sum + cur, sum + all, sum[cur] + avg) - sum - 1;
			tmp = sum[nxt] - sum[cur];
			if(nxt < all && tmp + seq[nxt] - avg < avg - tmp)
				tmp += seq[nxt++];
			len[i] = nxt - cur;
			low = min(low, tmp);
			upp = max(upp, tmp);
			cur = nxt;
		}
		if(upp - low < ans) {
			ans = upp - low;
			cur = 0;
			for(int j = 0; j < q; ++j)
				for(nxt = cur + len[j]; cur < nxt; ++cur) {
					int x = ord[cur] / m, y = ord[cur] % m;
					pos[x][y] = j;
				}
//			fprintf(stderr, "new: %lld\n", ans);
		}
	}
//	for(int i = 0; i < maxn >> 4; ++i) { // random
//		int cur = 0, nxt;
//		LL low = INF, upp = 0;
//		for(int i = 0; i < q; ++i) {
//			LL tmp = 0, rem = sum[all] - sum[cur], avg = rem / (q - i);
//			nxt = upper_bound(sum + cur, sum + all, sum[cur] + avg) - sum - 1;
//			tmp = sum[nxt] - sum[cur];
//			if(nxt < all && rand() % seq[nxt] < avg - tmp) // avg-tmp in [0, seq[nxt])
//				tmp += seq[nxt++];
//			len[i] = nxt - cur;
//			low = min(low, tmp);
//			upp = max(upp, tmp);
//			cur = nxt;
//		}
//		if(upp - low < ans) {
//			ans = upp - low;
//			cur = 0;
//			for(int j = 0; j < q; ++j)
//				for(nxt = cur + len[j]; cur < nxt; ++cur) {
//					int x = ord[cur] / m, y = ord[cur] % m;
//					pos[x][y] = j;
//				}
////			fprintf(stderr, "new: %lld\n", ans);
//		}
//	}
	if(!rev) {
		reverse(ord, ord + all);
		solve(1);
	}
}
int main() {
	srand(time(0));
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			scanf("%d", mat[i] + j);
	{ // LRLR
		int tot = 0;
		for(int i = 0; i < n; ++i)
			if(i & 1) {
				for(int j = m - 1; j >= 0; --j)
					ord[tot++] = i * m + j;
			} else {
				for(int j = 0; j < m; ++j)
					ord[tot++] = i * m + j;
			}
		solve();
	}
	{ // RLRL
		int tot = 0;
		for(int i = 0; i < n; ++i)
			if(i & 1) {
				for(int j = 0; j < m; ++j)
					ord[tot++] = i * m + j;
			} else {
				for(int j = m - 1; j >= 0; --j)
					ord[tot++] = i * m + j;
			}
		solve();
	}
	{ // DUDU
		int tot = 0;
		for(int i = 0; i < m; ++i)
			if(i & 1) {
				for(int j = n - 1; j >= 0; --j)
					ord[tot++] = j * m + i;
			} else {
				for(int j = 0; j < n; ++j)
					ord[tot++] = j * m + i;
			}
		solve();
	}
	{ // UDUD
		int tot = 0;
		for(int i = 0; i < m; ++i)
			if(i & 1) {
				for(int j = 0; j < n; ++j)
					ord[tot++] = j * m + i;
			} else {
				for(int j = n - 1; j >= 0; --j)
					ord[tot++] = j * m + i;
			}
		solve();
	}
	{ // C
		int tot = 0, x = 0, y = 0, d = 0;
		static bool vis[maxn][maxn] = {};
		while(!vis[x][y]) {
			vis[x][y] = 1;
			ord[tot++] = x * m + y;
			int nx = x + dx[d], ny = y + dy[d];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) {
				x = nx;
				y = ny;
			} else {
				d = (d + 1) & 3;
				x += dx[d];
				y += dy[d];
			}
		}
		solve();
	}
	{ // C
		int tot = 0, x = 0, y = m - 1, d = 1;
		static bool vis[maxn][maxn] = {};
		while(!vis[x][y]) {
			vis[x][y] = 1;
			ord[tot++] = x * m + y;
			int nx = x + dx[d], ny = y + dy[d];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) {
				x = nx;
				y = ny;
			} else {
				d = (d + 1) & 3;
				x += dx[d];
				y += dy[d];
			}
		}
		solve();
	}
	{ // C
		int tot = 0, x = n - 1, y = m - 1, d = 2;
		static bool vis[maxn][maxn] = {};
		while(!vis[x][y]) {
			vis[x][y] = 1;
			ord[tot++] = x * m + y;
			int nx = x + dx[d], ny = y + dy[d];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) {
				x = nx;
				y = ny;
			} else {
				d = (d + 1) & 3;
				x += dx[d];
				y += dy[d];
			}
		}
		solve();
	}
	{ // C
		int tot = 0, x = n - 1, y = 0, d = 3;
		static bool vis[maxn][maxn] = {};
		while(!vis[x][y]) {
			vis[x][y] = 1;
			ord[tot++] = x * m + y;
			int nx = x + dx[d], ny = y + dy[d];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) {
				x = nx;
				y = ny;
			} else {
				d = (d + 1) & 3;
				x += dx[d];
				y += dy[d];
			}
		}
		solve();
	}
	{ // CC
		int tot = 0, x = 0, y = 0, d = 1;
		static bool vis[maxn][maxn] = {};
		while(!vis[x][y]) {
			vis[x][y] = 1;
			ord[tot++] = x * m + y;
			int nx = x + dx[d], ny = y + dy[d];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) {
				x = nx;
				y = ny;
			} else {
				d = (d + 3) & 3;
				x += dx[d];
				y += dy[d];
			}
		}
		solve();
	}
	{ // CC
		int tot = 0, x = n - 1, y = 0, d = 0;
		static bool vis[maxn][maxn] = {};
		while(!vis[x][y]) {
			vis[x][y] = 1;
			ord[tot++] = x * m + y;
			int nx = x + dx[d], ny = y + dy[d];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) {
				x = nx;
				y = ny;
			} else {
				d = (d + 3) & 3;
				x += dx[d];
				y += dy[d];
			}
		}
		solve();
	}
	{ // CC
		int tot = 0, x = n - 1, y = m - 1, d = 3;
		static bool vis[maxn][maxn] = {};
		while(!vis[x][y]) {
			vis[x][y] = 1;
			ord[tot++] = x * m + y;
			int nx = x + dx[d], ny = y + dy[d];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) {
				x = nx;
				y = ny;
			} else {
				d = (d + 3) & 3;
				x += dx[d];
				y += dy[d];
			}
		}
		solve();
	}
	{ // CC
		int tot = 0, x = 0, y = m - 1, d = 2;
		static bool vis[maxn][maxn] = {};
		while(!vis[x][y]) {
			vis[x][y] = 1;
			ord[tot++] = x * m + y;
			int nx = x + dx[d], ny = y + dy[d];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m && !vis[nx][ny]) {
				x = nx;
				y = ny;
			} else {
				d = (d + 3) & 3;
				x += dx[d];
				y += dy[d];
			}
		}
		solve();
	}
	for(int i = 0; i < maxt; ++i) {
		int tot = 0, xL = 0, xR = n - 1, yL = 0, yR = m - 1, o = rand() & 3;
		while(tot < n * m) { // random end point
			int x = o & 2 ? xR : xL, y = ((o + 1) & 2) ? yR : yL;
			int nx = x + dx[(o + 1) & 3], ny = y + dy[(o + 1) & 3], d;
			bool chk1 = nx >= xL && nx <= xR && ny >= yL && ny <= yR;
			nx = x + dx[o];
			ny = y + dy[o];
			bool chk0 = nx >= xL && nx <= xR && ny >= yL && ny <= yR;
			if(chk0 && chk1)
				d = rand() & 1;
			else
				d = chk1;
			nx = x;
			ny = y;
			while(nx >= xL && nx <= xR && ny >= yL && ny <= yR) {
				ord[tot++] = nx * m + ny;
				nx += dx[(o + d) & 3];
				ny += dy[(o + d) & 3];
			}
			if(x == nx) {
				xL += x == xL;
				xR -= x == xR;
			}
			if(y == ny) {
				yL += y == yL;
				yR -= y == yR;
			}
			o = (o + (d ? 3 : 1)) & 3;
		}
		if(rand() & 1) { // random start point
			int x0 = ord[0] / m, y0 = ord[0] % m;
			int x1, y1;
			for(int d = 0; d < 4; ++d) {
				x1 = x0 + dx[d];
				y1 = y0 + dy[d];
				if(x1 >= 0 && x1 < n && y1 >= 0 && y1 < m && x1 * m + y1 != ord[1])
					break;
			}
			int pos = 0;
			for(int idx = x1 * m + y1; ord[pos] != idx; ++pos);
			reverse(ord, ord + pos);
		}
		solve();
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			printf("%d%c", pos[i][j] + 1, " \n"[j + 1 == m]);
	return 0;
}
