#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e3 + 1;

inline LL sqr(int x) {
    return (LL)x * x;
}

void solve() {
    int n, m;
    static int mat[maxn][maxn], sum[maxn], diff[maxn];
    static LL sum2[maxn];
    scanf("%d%d", &m, &n);
    for(int i = 0; i < n; ++i) {
        sum[i] = sum2[i] = 0;
        for(int j = 0; j < m; ++j) {
            scanf("%d", mat[i] + j);
            sum[i] += mat[i][j];
            sum2[i] += sqr(mat[i][j]);
        }
        if(i > 0)
            diff[i] = sum[i] - sum[i - 1];
    }
    int y, dt = (sum[n - 1] - sum[0]) / (n - 1);
    for(y = 1; y < n - 1 && diff[y] == dt; ++y);
    int adt = diff[y] - dt;
    LL dt2;
    if(y >= 3) {
        LL df2 = sum2[y - 2] - sum2[y - 3];
        LL df1 = sum2[y - 1] - sum2[y - 2];
        LL df0 = df1 - df2 + df1;
        dt2 = sum2[y] - (sum2[y - 1] + df0);
    } else {
        // y + 3 < n
        LL df2 = sum2[y + 3] - sum2[y + 2];
        LL df1 = sum2[y + 2] - sum2[y + 1];
        LL df0 = df1 - df2 + df1;
        dt2 = sum2[y] - (sum2[y + 1] - df0);
    }
    int x;
    for(x = 0; x < m && sqr(mat[y][x]) - sqr(mat[y][x] - adt) != dt2; ++x);
    printf("%d %d\n", y, mat[y][x] - adt);
    fflush(stdout);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
        solve();
	}
	return 0;
}