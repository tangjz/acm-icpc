#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 501;
int n, m, f[maxn][maxn];
bool g[maxn][maxn], vis[maxn][maxn];
struct Point {
    int x, y;
    void read() {
        scanf("%d%d", &x, &y);
    }
    bool operator == (Point const &t) const {
        return x == t.x && y == t.y;
    }
    bool operator < (Point const &t) const {
        return x < t.x || (x == t.x && y < t.y);
    }
    Point operator - (Point const &t) const {
        return (Point){x - t.x, y - t.y};
    }
    int dot(Point const &t) const {
        return x * t.x + y * t.y;
    }
    int det(Point const &t) const {
        return x * t.y - y * t.x;
    }
} a[maxn], b[maxn], stk[maxn];
inline int G(int L, int R) {
    if(g[L][R])
        return 1;
    if(vis[L][R])
        return f[L][R];
    vis[L][R] = 1;
    int &ret = f[L][R];
    ret = maxn;
    for(int i = 0; i < m; ++i)
        if(i != L && i != R && g[L][i])
            ret = min(ret, G(i, R) + 1);
    return ret;
}
int main() {
    while(scanf("%d", &n) == 1) {
        for(int i = 0; i < n; ++i)
            a[i].read();
        sort(a, a + n);
        n = unique(a, a + n) - a;
        scanf("%d", &m);
        int mm = m;
        for(int i = 0; i < m; ++i)
            b[i].read();
        sort(b, b + m);
        m = unique(b, b + m) - b;
        if(n == 1) { // check ans = 1
            int i;
            for(i = 0; i < m; ++i)
                if(a[0] == b[i])
                    break;
            if(i < m) {
                printf("%d\n", mm - 1);
                continue;
            }
        }
        { // check ans = 2
            bool chk = 0;
            for(int i = 0; i < m && !chk; ++i)
                for(int j = i + 1; j < m && !chk; ++j) {
                    bool tmp = 1;
                    for(int k = 0; k < n && tmp; ++k)
                        tmp &= !(b[j] - b[i]).det(a[k] - b[i]) && (b[i] - a[k]).dot(b[j] - a[k]) <= 0;
                    chk |= tmp;
                }
            if(chk) {
                printf("%d\n", mm - 2);
                continue;
            }
        }
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < m; ++j) {
                g[i][j] = i != j;
                for(int k = 0; k < n && g[i][j]; ++k)
                    g[i][j] &= (b[j] - b[i]).det(a[k] - b[i]) >= 0;
                vis[i][j] = 0;
            }
        int ans = maxn;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < m; ++j)
                if(g[i][j] && G(j, i) > 1)
                    ans = min(ans, G(j, i) + 1);
        if(ans < maxn)
            printf("%d\n", mm - ans);
        else
            puts("ToT");
    }
    return 0;
}
