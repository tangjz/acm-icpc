#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)5e4 + 1, maxc = 13, maxd = maxc << 2, maxs = (int)3e2 + 1;

void solve() {
    int n, q;
    scanf("%d%d", &n, &q);
    int sq = (int)ceil(sqrtl(n + n));
    static int pos[maxn], sum[maxd + 1][maxs], perm[maxd + 1][maxs];
    static int seq[maxd + 1][maxn];
    for(int i = 0; i < n; ++i) {
        pos[i] = i < sq ? 0 : pos[i - sq] + 1;
        if(!i || pos[i] > pos[i - 1])
            for(int j = 0; j < maxd; ++j) {
                sum[j][pos[i]] = 0;
                perm[j][pos[i]] = j;
            }
        for(int j = 0; j < maxd; ++j) {
            seq[j][i] = j % maxc + 1;
            sum[j][pos[i]] += seq[j][i];
        }
    }
    while(q--) {
        int typ, L, R, u, v;
        scanf("%d%d%d", &typ, &L, &R);
        int pL = pos[L], pR = pos[R];
        if(typ == 1) {
            int ret = 0;
            if(pL == pR) {
                for(int i = L; i <= R; ++i)
                    ret += seq[perm[maxd - 1][pL]][i];
            } else {
                for(int i = L; i < n && pos[i] == pL; ++i)
                    ret += seq[perm[maxd - 1][pL]][i];
                for(int i = R; i >= 0 && pos[i] == pR; --i)
                    ret += seq[perm[maxd - 1][pR]][i];
                for(int i = pL + 1; i < pR; ++i)
                    ret += sum[perm[maxd - 1][i]][i];
            }
            printf("%d\n", ret);
            continue;
        }
        scanf("%d%d", &u, &v);
        if(pL == pR) {
            for(int i = L; i <= R; ++i) {
                sum[perm[u][pL]][pL] -= seq[perm[u][pL]][i];
                sum[perm[v][pL]][pL] -= seq[perm[v][pL]][i];
                swap(seq[perm[u][pL]][i], seq[perm[v][pL]][i]);
                sum[perm[u][pL]][pL] += seq[perm[u][pL]][i];
                sum[perm[v][pL]][pL] += seq[perm[v][pL]][i];
            }
        } else {
            for(int i = L; i < n && pos[i] == pL; ++i) {
                sum[perm[u][pL]][pL] -= seq[perm[u][pL]][i];
                sum[perm[v][pL]][pL] -= seq[perm[v][pL]][i];
                swap(seq[perm[u][pL]][i], seq[perm[v][pL]][i]);
                sum[perm[u][pL]][pL] += seq[perm[u][pL]][i];
                sum[perm[v][pL]][pL] += seq[perm[v][pL]][i];
            }
            for(int i = R; i >= 0 && pos[i] == pR; --i) {
                sum[perm[u][pR]][pR] -= seq[perm[u][pR]][i];
                sum[perm[v][pR]][pR] -= seq[perm[v][pR]][i];
                swap(seq[perm[u][pR]][i], seq[perm[v][pR]][i]);
                sum[perm[u][pR]][pR] += seq[perm[u][pR]][i];
                sum[perm[v][pR]][pR] += seq[perm[v][pR]][i];
            }
            for(int i = pL + 1; i < pR; ++i)
                swap(perm[u][i], perm[v][i]);
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
