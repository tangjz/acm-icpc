#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200001, maxm = 2500001, BOUND = 1001;
int n, m, a[maxn], b[maxn], tot;
struct Treap {
    int lch, rch, size, val;
    long long sum;
} pool[maxm];
inline int randL() {
    return RAND_MAX == 0x7FFF ? rand() << 16 | rand() : rand();
}
int Snapshot(int rt) {
    pool[tot] = pool[rt];
    return tot++;
}
void Maintain(int rt) {
    int lch = pool[rt].lch, rch = pool[rt].rch;
    pool[rt].size = pool[lch].size + pool[rch].size + 1;
    pool[rt].sum = pool[lch].sum + pool[rch].sum + pool[rt].val;
}
pair<int, int> Split(int rt, int sz) {
    if(!rt)
        return make_pair(0, 0);
    int lch = pool[rt].lch, rch = pool[rt].rch;
    rt = Snapshot(rt);
    if(pool[lch].size + 1 > sz) {
        pair<int, int> tr = Split(lch, sz);
        pool[rt].lch = tr.second;
        Maintain(rt);
        return make_pair(tr.first, rt);
    } else {
        pair<int, int> tr = Split(rch, sz - pool[lch].size - 1);
        pool[rt].rch = tr.first;
        Maintain(rt);
        return make_pair(rt, tr.second);
    }
}
int Merge(int x, int y) {
    if(!x || !y) {
        return x | y;
    } else if(randL() % (pool[x].size + pool[y].size) < pool[x].size) {
        x = Snapshot(x);
        pool[x].rch = Merge(pool[x].rch, y);
        Maintain(x);
        return x;
    } else {
        y = Snapshot(y);
        pool[y].lch = Merge(x, pool[y].lch);
        Maintain(y);
        return y;
    }
}
int Pow(int x, int k) {
    int ret = 0;
    for( ; k > 0; k >>= 1, x = Merge(x, x))
        (k & 1) && (ret = Merge(ret, x));
    return ret;
}
int Segment(int rt, int L, int R) {
    return L <= R ? Split(Split(rt, R).first, L - 1).second : 0;
}
int Replace(int rt, int L, int R, int seg) {
    pair<int, int> tr1 = Split(rt, R);
    pair<int, int> tr2 = Split(tr1.first, L - 1);
    int tmp = Merge(tr2.first, seg);
    return Merge(tmp, tr1.second);
}
int Build(int sz, int a[]) {
    if(sz <= 0)
        return 0;
    int half = (sz - 1) >> 1, rt = tot++;
    pool[rt].lch = Build(half, a);
    pool[rt].val = a[half];
    pool[rt].rch = Build(sz - half - 1, a + half + 1);
    Maintain(rt);
    return rt;
}
void Rebuild(int rt, int a[]) {
    if(!rt)
        return;
    int lch = pool[rt].lch, rch = pool[rt].rch;
    Rebuild(lch, a);
    a[pool[lch].size] = pool[rt].val;
    Rebuild(rch, a + pool[lch].size + 1);
}
int main() {
    srand(time(0));
    while(scanf("%d%d", &n, &m) == 2) {
        tot = 1;
        for(int i = 0; i < n; ++i)
            scanf("%d", a + i);
        int rtA = Build(n, a), rtB = rtA, tim = tot;
        while(m--) {
            int typ, L, R, x;
            scanf("%d%d%d", &typ, &L, &R);
            if(typ == 1) {
                int tmp = tot, seg = Segment(rtB, L, R);
                printf("%I64d\n", pool[seg].sum);
                tot = tmp;
            } else if(typ == 2) {
                scanf("%d", &x);
                int seg = Pow(Segment(rtB, L - x, L - 1), (R - L + 1) / x);
                if((R - L + 1) % x > 0)
                    seg = Merge(seg, Segment(rtB, L - x, L - x + (R - L) % x));
                rtB = Replace(rtB, L, R, seg);
            } else {
                int seg = Segment(rtA, L, R);
                rtB = Replace(rtB, L, R, seg);
            }
            if(tot + BOUND > maxm) {
                Rebuild(rtB, b);
                tot = tim;
                rtB = Build(n, b);
            }
        }
    }
    return 0;
}