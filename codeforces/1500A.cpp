#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;

const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)2e5 + 9, maxm = (int)5e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n;
	scanf("%d", &n);
	static int a[maxn], ord[maxn];
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		ord[i] = i;
	}
	sort(ord + 1, ord + n + 1, [&](int const &u, int const &v) {
		return a[u] < a[v];
	});
	int m = 0, cnt = 0;
	static int sp[maxn], sp2[maxn], ans[4];
	for(int i = 1, j; i <= n && cnt < 2; ) {
		for(j = i; j <= n && a[ord[i]] == a[ord[j]]; ++j);
		sp2[m] = i + 1 < j ? ord[i + 1] : 0;
		sp[m++] = ord[i];
		for( ; cnt < 2 && i + 1 < j; ++cnt) {
			ans[cnt] = ord[i++];
			ans[cnt + 2] = ord[i++];
		}
		i = j;
	}
	if(cnt == 2) {
		cnt <<= 1;
	} else {
		int mx = a[sp[m]] << 1;
		static pair<int, int> vis[maxm];
		memset(vis, 0, mx * sizeof(vis[0]));
		cnt = 0;
		for(int i = 0; cnt < 4 && i < m; ++i)
			for(int j = i + 1; cnt < 4 && j < m; ++j) {
				int sum = a[sp[i]] + a[sp[j]];
				if(!vis[sum].first) {
					vis[sum] = make_pair(sp[i], sp[j]);
				} else {
					cnt = 4;
					ans[0] = vis[sum].first;
					ans[1] = vis[sum].second;
					ans[2] = sp[i];
					ans[3] = sp[j];
				}
			}
		for(int i = 0; cnt < 4 && i < m; ++i) {
			if(!sp2[i])
				continue;
			int sum = a[sp[i]] << 1;
			if(!vis[sum].first)
				continue;
			cnt = 4;
			ans[0] = vis[sum].first;
			ans[1] = vis[sum].second;
			ans[2] = sp[i];
			ans[3] = sp2[i];
		}
	}
	if(cnt == 4) {
		puts("YES");
		for(int i = 0; i < cnt; ++i)
			printf("%d%c", ans[i], " \n"[i == cnt - 1]);
	} else {
		puts("NO");
	}
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