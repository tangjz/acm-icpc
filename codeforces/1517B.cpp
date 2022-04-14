#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
    const int maxn = 101;
    int n, m;
    static int seq[maxn][maxn], pL[maxn], pR[maxn];
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j)
            scanf("%d", seq[i] + j);
        sort(seq[i], seq[i] + m);
        pL[i] = 0;
        pR[i] = m - 1;
    }
    static int ans[maxn][maxn];
    for(int i = 0; i < m; ++i) {
        int low = 0;
        for(int j = 1; j < n; ++j)
            if(seq[low][pL[low]] > seq[j][pL[j]])
                low = j;
        for(int j = 0; j < n; ++j)
            ans[j][i] = j == low ? seq[j][pL[j]++] : seq[j][pR[j]--];
    }
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            printf("%d%c", ans[i][j], " \n"[j == m - 1]);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
        solve();
		// printf("%lld\n", solve());
	}
	return 0;
}