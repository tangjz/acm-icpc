#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = (int)5e4 + 1, maxm = maxn << 1 | 1;

int n, seg[maxn][3], ord[maxn];
int seq[maxm], bits[maxm], rem[maxm], dsu[maxm];

inline bool cmp(int const &u, int const &v) {
    return seg[u][0] < seg[v][0];
}

int dsuFind(int x) {
    return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu[x]));
}

void solve() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        int &L = seg[i][0], &R = seg[i][1], &D = seg[i][2];
        scanf("%d%d%d", &L, &R, &D);
        ++R;
        seq[i << 1] = L;
        seq[i << 1 | 1] = R;
        ord[i] = i;
    }
    sort(ord, ord + n, cmp);
    sort(seq, seq + n + n);
    int m = unique(seq, seq + n + n) - seq;
    for(int i = 0; i + 1 < m; ++i) {
        bits[i] = 0;
        rem[i] = seq[i + 1] - seq[i];
        dsu[i] = -1;
    }
    dsu[m - 1] = -1;
    int ans = 0;
    for(int o = n - 1; o >= 0; --o) {
        int *las = seg[ord[o]];
        int L = lower_bound(seq, seq + m, las[0]) - seq;
        int R = lower_bound(seq, seq + m, las[1]) - seq;
        int D = las[2];
        // printf("proc [%d, %d) %d\n", seq[L], seq[R], D);
        for(int x = L + 1; x < m; x += x & -x)
            D -= bits[x - 1];
        for(int x = R + 1; x < m; x += x & -x)
            D += bits[x - 1];
        // printf("rem %d\n", D);
        if(D <= 0)
            continue;
        ans += D;
        for(int i = dsuFind(L); ; i = dsuFind(i)) {
            assert(i < R);
            int com = min(rem[i], D);
            // printf("use [%d, %d) %d\n", seq[i], seq[i + 1], com);
            for(int x = i + 1; x > 0; x -= x & -x)
                bits[x - 1] += com;
            if(!(rem[i] -= com))
                dsu[i] = i + 1;
            if(!(D -= com))
                break;
        }
    }
    printf("%d\n", ans);
}

int main() {
    int T = 1;
    // scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
