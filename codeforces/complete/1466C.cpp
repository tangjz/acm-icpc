#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;

const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)1e5 + 1, maxm = (int)2e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	const int INF = 0x3f3f3f3f;
	static char buf[maxn];
	scanf("%s", buf);
	int n = strlen(buf);
	if(n <= 2) {
		puts(n == 2 && buf[0] == buf[1] ? "1" : "0");
		return;
	}
	int dp[2][4], cur = 1, pre = 0;
	dp[cur][0] = buf[0] == buf[1] ? INF : 0;
	dp[cur][1] = dp[cur][2] = 1;
	dp[cur][3] = 2;
	for(int i = 2; i < n; ++i) {
		swap(cur, pre);
		memset(dp[cur], 0x3f, sizeof(dp[0]));
		for(int j = 0; j < 4; ++j) {
			if(dp[pre][j] == INF)
				continue;
			for(int o = 0; o < 2; ++o) {
				int k = (j << 1 | o) & 3;
				if(!o && ((buf[i - 1] == buf[i] && !(j & 1)) || (buf[i - 2] == buf[i] && !(j & 2))))
					continue;
				dp[cur][k] = min(dp[cur][k], dp[pre][j] + o);
			}
		}
	}
	int ans = INF;
	for(int i = 0; i < 4; ++i)
		ans = min(ans, dp[cur][i]);
	printf("%d\n", ans);
}

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
