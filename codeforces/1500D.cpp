#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;

const int mod = (int)1e9 + 7, maxd = 11, maxc = 26;
const int maxn = 1501, maxm = (int)2.3e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n, q;
	scanf("%d%d", &n, &q);
	int m = n * n, st = 0, cur = 0, pre = 1;
	static int ans[maxn], tim[maxm];
	static pair<int, int> info[2][maxn][maxd];
	memset(tim, 0, (m + 1) * sizeof(int));
	memset(ans, 0, (n + 1) * sizeof(int));
	for(int i = 0; i < n; ++i) {
		info[cur][i][0] = make_pair(n + 1, 0);
	}
	for(int i = 0; i < n; ++i) {
		swap(cur, pre);
		for(int j = 0, col; j < n; ++j) {
			scanf("%d", &col);
			info[cur][j][0] = make_pair(1, col);
			++st;
			tim[col] = st;
			int tot = 0, pos = 1, idx[3] = {};
			pair<int, int> *que[3];
			if(i > 0) {
				que[tot++] = info[pre][j];
				if(j > 0)
					que[tot++] = info[pre][j - 1];
			}
			if(j > 0)
				que[tot++] = info[cur][j - 1];
			int upp = min(i, j) + 2;
			while(true) {
				int low = upp;
				for(int k = 0; k < tot; ++k)
					low = min(low, que[k][idx[k]].first + 1);
				// printf("low: %d upp: %d\n", low, upp);
				if(low >= upp)
					break;
				int old_pos = pos;
				bool bad = 0;
				for(int k = 0; !bad && k < tot; ++k)
					for( ; que[k][idx[k]].first + 1 == low; ++idx[k]) {
						col = que[k][idx[k]].second;
						if(!col) {
							bad = 1;
							break;
						}
						// printf("pick %d\n", col);
						if(tim[col] == st)
							continue;
						tim[col] = st;
						if(pos == q) {
							bad = 1;
							break;
						}
						info[cur][j][pos++] = make_pair(low, col);
					}
				if(bad) {
					pos = old_pos;
					upp = low;
					break;
				}
			}
			info[cur][j][pos] = make_pair(upp, 0);
			// printf("%d %d:", i, j);
			// for(int k = 0; k <= pos; ++k)
			// 	printf(" %d(%d)", info[cur][j][k].second, info[cur][j][k].first);
			// puts("");
			++ans[upp - 1];
		}
	}
	for(int i = n; i > 0; --i)
		ans[i - 1] += ans[i];
	for(int i = 1; i <= n; ++i)
		printf("%d\n", ans[i]);
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