#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxd = 17, maxm = maxn * maxd * 6 + 1;
int t, n, m, tot, col[maxn], fa[maxn], dep[maxn];
int rtC[maxn], rtD[maxn], lch[maxm], rch[maxm], val[maxm];
void seg_upd(int &cur, int L, int R, int x, int v) {
    int las = cur;
    cur = ++tot;
    lch[cur] = lch[las];
    rch[cur] = rch[las];
    val[cur] = val[las] + v;
    if(L == R)
        return;
    int M = (L + R) >> 1;
    if(x <= M)
        seg_upd(lch[cur], L, M, x, v);
    else
        seg_upd(rch[cur], M + 1, R, x, v);
}
void seg_mix(int &cur, int adt, int L, int R) {
    if(!cur || !adt) {
        cur = cur + adt;
        return;
    }
    int las = cur;
    cur = ++tot;
    lch[cur] = lch[las];
    rch[cur] = rch[las];
    val[cur] = val[las] + val[adt];
    if(L == R)
        return;
    int M = (L + R) >> 1;
    seg_mix(lch[cur], lch[adt], L, M);
    seg_mix(rch[cur], rch[adt], M + 1, R);
}
void col_mix(int &curC, int &curD, int adt, int L, int R) {
    if(!curD || !adt) {
        curD = curD + adt;
        return;
    }
    int las = curD;
    curD = ++tot;
    lch[curD] = lch[las];
    rch[curD] = rch[las];
    if(L == R) {
        val[curD] = min(val[las], val[adt]);
        seg_upd(curC, 1, n, max(val[las], val[adt]), -1);
        return;
    }
    int M = (L + R) >> 1;
    col_mix(curC, lch[curD], lch[adt], L, M);
    col_mix(curC, rch[curD], rch[adt], M + 1, R);
}
int seg_que(int cur, int L, int R, int x) {
    if(R <= x)
        return val[cur];
    int M = (L + R) >> 1;
    return seg_que(lch[cur], L, M, x) + (M < x ? seg_que(rch[cur], M + 1, R, x) : 0);
}
int main() {
    scanf("%d", &t);
    while(t--) {
        tot = 0;
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i)
            scanf("%d", col + i);
        dep[1] = 1;
        for(int i = 2; i <= n; ++i) {
            scanf("%d", fa + i);
            dep[i] = dep[fa[i]] + 1;
        }
        for(int i = 1; i <= n; ++i) {
            seg_upd(rtC[i] = 0, 1, n, dep[i], 1);
            seg_upd(rtD[i] = 0, 1, n, col[i], dep[i]);
        }
        for(int i = n; i > 1; --i) {
            int p = fa[i];
            seg_mix(rtC[p], rtC[i], 1, n);
            col_mix(rtC[p], rtD[p], rtD[i], 1, n);
        }
        int last = 0;
        while(m--) {
            int x, d;
            scanf("%d%d", &x, &d);
            x ^= last;
            d ^= last;
            printf("%d\n", last = seg_que(rtC[x], 1, n, dep[x] + d));
        }
    }
    return 0;
}
