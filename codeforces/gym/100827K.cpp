#include <bits/stdc++.h>
using namespace std;

const int maxn = 5;
int n, mat[maxn][maxn];
int rmsk[maxn], rlim[2][maxn], rpre[maxn][maxn + 2];
int cmsk[maxn], clim[2][maxn], cpre[maxn][maxn + 2];

bool dfs(int x, int y) {
    if(x == n)
        return 1;
    int nx = x, ny = y + 1;
    if(ny == n) {
        ++nx;
        ny = 0;
    }
    int L = 0, R = n - 1;
    if(mat[x][y] != -1) {
        L = R = mat[x][y];
    }
    for(int i = L, skip = (rmsk[x] | cmsk[y]) >> L; i <= R; ++i, skip >>= 1) {
        if(L != R && (skip & 1))
            continue;
        bool ban = 0;
        mat[x][y] = i;
        if(rlim[0][x]) {
            if(!rpre[x][0] || rpre[x][rpre[x][0]] < i)
                rpre[x][++rpre[x][0]] = i;
            ban |= y == n - 1 ? (rpre[x][0] != rlim[0][x]) : (rpre[x][0] > rlim[0][x]);
        }
        if(clim[0][y]) {
            if(!cpre[y][0] || cpre[y][cpre[y][0]] < i)
                cpre[y][++cpre[y][0]] = i;
            ban |= x == n - 1 ? (cpre[y][0] != clim[0][y]) : (cpre[y][0] > clim[0][y]);
        }
        if(!ban && y == n - 1 && rlim[1][x]) {
            int sz = 0, upp = -1;
            for(int j = n - 1; j >= 0; --j)
                if(upp < mat[x][j]) {
                    ++sz;
                    upp = mat[x][j];
                }
            ban |= sz != rlim[1][x];
        }
        if(!ban && x == n - 1 && clim[1][y]) {
            int sz = 0, upp = -1;
            for(int j = n - 1; j >= 0; --j)
                if(upp < mat[j][y]) {
                    ++sz;
                    upp = mat[j][y];
                }
            ban |= sz != clim[1][y];
        }
        if(!ban) {
            if(L != R) {
                rmsk[x] ^= 1 << i;
                cmsk[y] ^= 1 << i;
            }
            if(dfs(nx, ny))
                return 1;
            if(L != R) {
                cmsk[y] ^= 1 << i;
                rmsk[x] ^= 1 << i;
            }
        }
        if(clim[0][y])
            cpre[y][0] -= cpre[y][cpre[y][0]] == i;
        if(rlim[0][x])
            rpre[x][0] -= rpre[x][rpre[x][0]] == i;
    }
    if(L != R)
        mat[x][y] = -1;
    return 0;
}

void solve() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        rmsk[i] = cmsk[i] = rpre[i][0] = cpre[i][0] = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            mat[i][j] = 0;
    bool ban = 0;
    for(int i = -1; i <= n; ++i) {
        static char buf[maxn + 4];
        scanf("%s", buf);
        for(int j = 0; j < n + 2; ++j)
            buf[j] = buf[j] == '-' ? 0 : (buf[j] - '0');
        if(i == -1 || i == n) {
            int idx = i == n;
            for(int j = 0; j < n; ++j)
                clim[idx][j] = buf[j + 1];
            continue;
        }
        rlim[0][i] = buf[0];
        rlim[1][i] = buf[n + 1];
        for(int j = 0; j < n; ++j) {
            mat[i][j] = (int)buf[j + 1] - 1;
            if(mat[i][j] == -1)
                continue;
            int tmp = 1 << mat[i][j];
            ban |= (rmsk[i] | cmsk[j]) & tmp;
            rmsk[i] |= tmp;
            cmsk[j] |= tmp;
        }
    }
    if(ban || !dfs(0, 0)) {
        puts("no");
    } else {
        static char buf[maxn + 2];
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j)
                buf[j] = '1' + mat[i][j];
            buf[n] = '\0';
            puts(buf);
        }
    }
    puts("");
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}