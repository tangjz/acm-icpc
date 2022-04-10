#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
const int maxn = (int)1e2 + 9, maxm = (int)1e6 + 9, maxd = 26;
const int mod = (int)1e9 + 7;
const DB eps = (DB)1e-12, pi = acos((DB)-1);

inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}

void solve() {
    int n, m, h;
    scanf("%d%d%d", &n, &m, &h);
    bool flip = 0;
    if(m & 1) {
        flip = 1;
        swap(n, m);
        h = n * m / 2 - h;
    }
    int sta = (n & 1) * (m >> 1);
    if(h < sta || (h - sta) & 1) {
        puts("NO");
        return;
    }
    puts("YES");
    static char ans[maxn][maxn];
    static int st = 0, tim[maxd] = {};
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            ans[i][j] = '\0';
    auto touch = [&](int x, int y) {
        for(int dx = -1; dx <= 1; ++dx)
            for(int dy = -1; dy <= 1; ++dy) {
                if(!!dx == !!dy)
                    continue;
                int xx = x + dx, yy = y + dy;
                if(xx < 0 || xx >= n || yy < 0 || yy >= m || ans[xx][yy] == '\0')
                    continue;
                tim[(int)(ans[xx][yy] - 'a')] = st;
            }
    };
    auto clear_time = [&]() {
        if(!(++st)) {
            ++st;
            memset(tim, 0, sizeof tim);
        }
    };
    auto get_color = [&](int x, int y) -> char {
        for(int i = 0; i < maxd; ++i)
            if(tim[i] != st)
                return 'a' + i;
        return '\0';
    };
    if(n & 1) {
        for(int j = 0; j < m; j += 2) {
            clear_time();
            touch(n - 1, j);
            touch(n - 1, j + 1);
            ans[n - 1][j] = ans[n - 1][j + 1] = get_color(n - 1, j);
            --h;
        }
    }
    for(int i = 0; i + 1 < n && h > 0; i += 2)
        for(int j = 0; j < m && h > 0; j += 2) {
            clear_time();
            touch(i, j);
            touch(i, j + 1);
            ans[i][j] = ans[i][j + 1] = get_color(i, j);
            --h;
            clear_time();
            touch(i + 1, j);
            touch(i + 1, j + 1);
            ans[i + 1][j] = ans[i + 1][j + 1] = get_color(i + 1, j);
            --h;
        }
    for(int i = 0; i + 1 < n; ++i)
        for(int j = 0; j < m; ++j) {
            if(ans[i][j] != '\0' || ans[i + 1][j] != '\0')
                continue;
            clear_time();
            touch(i, j);
            touch(i + 1, j);
            ans[i][j] = ans[i + 1][j] = get_color(i, j);
        }
    if(flip) {
        swap(n, m);
        for(int i = 0; i < n || i < m; ++i)
            for(int j = 0; j < i; ++j)
                swap(ans[i][j], ans[j][i]);
    }
    for(int i = 0; i < n; ++i) {
        ans[i][m] = '\0';
        puts(ans[i]);
    }
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: %d\n", Case, solve());
        solve();
    }
    return 0;
}