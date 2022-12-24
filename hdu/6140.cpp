#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 1001;
int t, n, m, a[maxn], mx, low, upp;
bool vis[maxn << 1 | 1];
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        mx = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            mx = std::max(mx, a[i]);
        }
        low = upp = 0;
        memset(vis, 0, (mx << 1 | 1) * sizeof(bool));
        vis[mx] = 1;
        for(int i = 1; i <= n; ++i) {
            char typ[3];
            scanf("%s", typ);
            if(typ[0] != 'D') {
                if(upp > mx)
                    upp += a[i];
                for(int j = mx; j >= -mx; --j)
                    if(vis[mx + j]) {
                        if(j + a[i] <= mx)
                            vis[mx + j + a[i]] = 1;
                        else
                            upp = std::max(upp, j + a[i]);
                    }
            }
            if(typ[0] != 'L') {
                if(low < -mx)
                    low -= a[i];
                for(int j = -mx; j <= mx; ++j)
                    if(vis[mx + j]) {
                        if(j - a[i] >= -mx)
                            vis[mx + j - a[i]] = 1;
                        else
                            low = std::min(low, j - a[i]);
                    }
            }
        }
        puts((m < -mx ? low <= m : (m > mx ? m <= upp : vis[mx + m])) ? "yes" : "no");
    }
    return 0;
}