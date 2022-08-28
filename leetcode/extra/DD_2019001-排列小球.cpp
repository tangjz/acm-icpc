#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    if(a > c)
        swap(a, c);
    if(b > c)
        swap(b, c);
    if(a > b)
        swap(a, b);
    if(!c) {
        puts("1");
        return 0;
    }
    typedef long long LL;
    vector<vector<vector<LL> > > dp(3, vector<vector<LL> >(a + 1, vector<LL>(b + 1)));
    dp[2][0][0] = 1;
    if(b)
        dp[1][0][1] = 1;
    if(a)
        dp[0][1][0] = 1;
    for(int len = 2; len <= a + b + c; ++len)
        for(int i = a; i >= 0; --i)
            for(int j = b; j >= 0; --j) {
                int k = len - i - j;
                if(k < 0 || k > c)
                    continue;
                if(k)
                    dp[2][i][j] = dp[0][i][j] + dp[1][i][j];
                if(j)
                    dp[1][i][j] = dp[0][i][j - 1] + dp[2][i][j - 1];
                if(i)
                    dp[0][i][j] = dp[1][i - 1][j] + dp[2][i - 1][j];
                // printf("len %d i %d j %d k %d: %lld %lld %lld\n", len, i, j, k, dp[0][i][j], dp[1][i][j], dp[2][i][j]);
            }
    LL ans = dp[0][a][b] + dp[1][a][b] + dp[2][a][b];
    printf("%lld\n", ans);
    return 0;
}
