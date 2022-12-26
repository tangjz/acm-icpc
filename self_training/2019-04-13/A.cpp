#include <bits/stdc++.h>
using namespace std;
const int maxn = 21, maxs = 401;
int t, n, m, tot, out[maxs][2];
bool validate() {
	if(tot < n * m) {
		int low = min(n, m), upp = max(n, m);
		if(low == 2)
			return upp <= 4;
		if(low == 3)
			return upp <= 3;
		return 0;
	}
	static bool vis[maxn][maxn];
	memset(vis, 0, sizeof vis);
	int px, py, cx = out[0][0], cy = out[0][1];
	vis[cx][cy] = 1;
	for(int i = 1; i < tot; ++i) {
		px = cx;
		py = cy;
		cx = out[i][0];
		cy = out[i][1];
		if(vis[cx][cy]) {
			printf("(%d, %d) duplicated\n", cx, cy);
			return 0;
		}
		vis[cx][cy] = 1;
		if(px == cx || py == cy || px - py == cx - cy || px + py == cx + cy) {
			printf("(%d, %d) (%d, %d) colinear\n", px, py, cx, cy);
			return 0;
		}
	}
	return 1;
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		tot = 0;
		scanf("%d%d", &n, &m);
		bool rev = 0;
		if(n > m) {
			swap(n, m);
			rev = 1;
		}
		auto append = [&](int x, int y) {
			assert(0 <= x && x < n);
			assert(0 <= y && y < m);
			out[tot][0] = x;
			out[tot][1] = y;
			++tot;
		};
		if(n == 2) {
			if(m >= 5) {
				for(int i = 0; i < m; ++i) {
					append(0, (i + 2) % m);
					append(1, i);
				}
			}
		} else if(n == 3) {
			if(m >= 4) {
				for(int i = 0; i < m; ++i) {
					append(0, i);
					append(1, (i + 2) % m);
					append(2, i);
				}
			}
		} else if(n == 4 && m == 4) {
			vector<int> idx = vector<int>{3, 0, 1, 2};
			for(int i : idx) {
				append(0, i);
				append(1, (i + 2) % m);
				append(2, i);
				append(3, (i + 2) % m);
			}
		} else { // n >= 4 && m >= 5
			if(n & 1) {
				for(int i = 0; i < m; ++i) {
					append(0, i);
					append(1, (i + 2) % m);
					append(2, i);
				}
			}
			for(int i = n & 1 ? 3 : 0; i < n; i += 2)
				for(int j = 0; j < m; ++j) {
					append(i, (j + 2) % m);
					append(i + 1, j);
				}
		}
		if(rev) {
			for(int i = 0; i < tot; ++i)
				swap(out[i][0], out[i][1]);
			swap(n, m);
			rev = 0;
		}
		printf("Case #%d: %s\n", Case, tot == n * m ? "POSSIBLE" : "IMPOSSIBLE");
		for(int i = 0; i < tot; ++i)
			printf("%d %d\n", out[i][0] + 1, out[i][1] + 1);
		// printf("%s\n", validate() ? "True" : "False");
	}
	return 0;
}