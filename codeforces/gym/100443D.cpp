#include <bits/stdc++.h>
using namespace std;

const int maxd = 21, maxl = 101, maxe = 31;
const double INF = 1e20;

int n, len[maxd];
char buf[maxd][maxl];

bool dfs(int dep, int adt) {
    // fprintf(stderr, "dep %d adt %d len %d: %s\n", dep, adt, len[dep], buf[dep]);
    if(n - dep < maxe && adt + len[dep] > (1 << (n - dep)) - 1)
        return 0;
    if(dep == n || !len[dep])
        return 1;
    if(len[dep] == 1 && adt <= 1) {
        if(buf[dep][0] == 'R')
            adt = adt ? 5 : 2;
        return n - dep >= maxe || adt + 1 <= (1 << (n - dep)) - 1;
    }
    char fir = '?';
    int &sz = len[dep + 1] = 0;
    for(int i = 0; i < len[dep]; ++i)
        if((adt + i) & 1) {
            buf[dep + 1][sz++] = buf[dep][i];
        } else {
            bool isR = buf[dep][i] == 'R';
            bool odd = ((adt + i) >> 1) & 1;
            char tmp = "LR"[isR ^ odd];
            if(fir == '?') {
                fir = tmp;
            } else if(fir != tmp) {
                return 0;
            }
        }
    adt >>= 1;
    if(fir == '?')
        return dfs(dep + 1, adt) || dfs(dep + 1, adt + 1);
    return dfs(dep + 1, adt + (fir == 'R'));
}

void solve() {
    scanf("%d%s", &n, buf[0]);
    len[0] = strlen(buf[0]);
    puts(dfs(0, 0) || dfs(0, 1) ? "Yes" : "No");
}

int main() {
    int T;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        printf("Case %d: ", Case);
        solve();
    }
    return 0;
}