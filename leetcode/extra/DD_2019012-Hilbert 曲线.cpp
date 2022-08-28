#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e3 + 1;

int main() {
    int n;
    scanf("%d", &n);
    vector<vector<int> > f(n, vector<int>(n)), g(n, vector<int>(n));
    f[0][0] = 1;
    for(int m = 1; m < n; m <<= 1) {
        int adt = m * m;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < m; ++j) {
                g[i][j] = f[i][j] + adt;
                g[i][j + m] = f[i][j] + adt + adt;
                g[i + m][j] = f[m - 1 - j][m - 1 - i];
                g[i + m][j + m] = f[j][i] + adt + adt + adt;
            }
        f.swap(g);
    }
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            printf("%d%c", f[i][j], " \n"[j == n - 1]);
    return 0;
}
