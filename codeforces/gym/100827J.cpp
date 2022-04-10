#include <bits/stdc++.h>
using namespace std;

const int maxn = 301, maxm = 81;

template<class T>
int solve(int n, int m, T mat[maxn]) {
    int best = 0, sx = -1, sy = -1, ty = m;
    static char buf[maxn];
    static T rem[maxn], tmp;
    for(int i = 0; i < n; ++i) {
        scanf("%s", buf);
        mat[i].reset();
        for(int j = 0; j < m; ++j)
            if(buf[j] == '#') {
                ++best;
                mat[i].set(j);
                if(sx == -1) {
                    sx = i;
                    sy = j;
                }
                ty = min(ty, j);
            }
    }
    if(!best)
        return 0;
    for(int dx = 1; sx + dx < n; ++dx)
        for(int dy = dx ? -sy : 1; sy + dy < m; ++dy) {
            int cnt = 0, adt;
            for(int i = n - 1; i >= sx; --i) {
                rem[i] = mat[i];
                if(i + dx >= n)
                    continue;
                tmp = rem[i] & (dy > 0 ? rem[i + dx] >> dy : rem[i + dx] << -dy);
                adt = tmp.count();
                if(!adt)
                    continue;
                cnt += adt;
                rem[i] ^= tmp;
                rem[i + dx] ^= dy > 0 ? tmp << dy : tmp >> -dy;
            }
            for(int i = sx; i < n; ++i) {
                tmp = rem[i];
                adt = tmp.count();
                if(!adt)
                    continue;
                if(i + dx < n)
                    tmp &= ~(dy > 0 ? mat[i + dx] >> dy : mat[i + dx] << -dy);
                if(tmp.any()) {
                    cnt = best + 1;
                    break;
                }
                cnt += adt;
            }
            best = min(best, cnt);
        }
    // dx = 0
    for(int i = n; i < m; ++i)
        mat[i].reset();
    for(int i = 0; i < max(n, m); ++i)
        for(int j = i + 1; j < max(n, m); ++j) {
            bool u = mat[i].test(j), v = mat[j].test(i);
            if(u == v)
                continue;
            mat[i].flip(j);
            mat[j].flip(i);
        }
    for(int dy = 1; sy + dy < m; ++dy) {
        int cnt = 0, adt;
        for(int i = m - 1; i >= ty; --i) {
            rem[i] = mat[i];
            if(i + dy >= m)
                continue;
            tmp = rem[i] & rem[i + dy];
            adt = tmp.count();
            if(!adt)
                continue;
            cnt += adt;
            rem[i] ^= tmp;
            rem[i + dy] ^= tmp;
        }
        for(int i = ty; i < m; ++i) {
            tmp = rem[i];
            adt = tmp.count();
            if(!adt)
                continue;
            if(i + dy < m)
                tmp &= ~mat[i + dy];
            if(tmp.any()) {
                cnt = best + 1;
                break;
            }
            cnt += adt;
        }
        best = min(best, cnt);
    }
    return best;
}

void solve() {
    int n, m;
    static bitset<maxn> large[maxn];
    static bitset<maxm> small[maxn];
    scanf("%d%d", &n, &m);
    printf("%d\n", max(n, m) < maxm ? solve(n, m, small) : solve(n, m, large));
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}