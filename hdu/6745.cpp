#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1;
int dp[maxn][maxn];
inline void upd_max(int &x, int y) {
    x < y && (x = y);
}
int main() {
    for(int i = 1; i < maxn; ++i)
        for(int j = 1; j < maxn; ++j) {
            if(i > 1)
                upd_max(dp[i][j], dp[i - 1][j]);
            if(j > 1)
                upd_max(dp[i][j], dp[i][j - 1]);
            dp[i][j] += __gcd(i, j) == 1;
        }
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        printf("%d\n", dp[n][m]);
    }
    return 0;
}
