#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
    const int maxn = 501;
    int n;
    static int perm[maxn], mat[maxn][maxn];
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", perm + i);
        for(int j = 1; j <= i; ++j)
            mat[i][j] = 0;
    }
    for(int i = 1; i <= n; ++i) {
        int cnt = perm[i], x = i, y = i;
        mat[x][y] = perm[i];
        --cnt;
        while(cnt > 0) {
            if(y > 1 && !mat[x][y - 1]) {
                --y;
            } else if(x < n) {
                assert(!mat[x + 1][y]);
                ++x;
            } else {
                assert(0);
            }
            mat[x][y] = perm[i];
            --cnt;
        }
    }
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= i; ++j)
            printf("%d%c", mat[i][j], " \n"[j == i]);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
        solve();
		// printf("%lld\n", solve());
	}
	return 0;
}