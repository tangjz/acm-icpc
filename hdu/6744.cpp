#include <bits/stdc++.h>
using namespace std;
const int maxm = 5, maxn = (int)4e2 + 1, maxd = 10;
const int data[maxd + 1][2] = {
    {60, 10}, {62, 17}, {65, 20}, {67, 23}, {70, 27},
    {75, 30}, {80, 33}, {85, 37}, {90, 40}, {95, 43}
};
int dp[maxm][maxn];
inline void upd_max(int &x, int y) {
    x < y && (x = y);
}
int main() {
    for(int i = 1; i < maxm; ++i)
        for(int j = 0; j < maxd; ++j) {
            int c = data[j][0], w = data[j][1];
            for(int k = c; k < maxn; ++k)
                upd_max(dp[i][k], dp[i - 1][k - c] + w);
        }
    int T;
    scanf("%d", &T);
    while(T--) {
        int n;
        scanf("%d", &n);
        int ans = dp[maxm - 1][n];
        printf("%d.%d\n", ans / 10, ans % 10);
    }
    return 0;
}
