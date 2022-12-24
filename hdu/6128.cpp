#include <map>
#include <ctime>
#include <cstdio>
#include <cstdlib>
typedef long long LL;
const int maxn = 100001;
int randL() {
    return RAND_MAX == 0x7FFF ? rand() << 16 | rand() : rand();
}
int randLL() {
    return (LL)randL() << 32 | randL();
}
LL mod_add(LL x, LL y, LL p) {
    return (x += y) < p ? x : x - p;
}
LL mod_sub(LL x, LL y, LL p) {
    return (x -= y) < 0 ? x + p : x;
}
LL mod_mul(LL x, LL y, LL p) {
    return (__int128_t)x * y % p;
}
LL mod_pow(LL x, LL y, LL p) {
    LL ret = 1;
    for( ; y > 0; y >>= 1, x = mod_mul(x, x, p))
        if(y & 1)
            ret = mod_mul(ret, x, p);
    return ret;
}
LL B, P;
struct Pair {
    LL x, y;
    Pair operator * (Pair const &t) const {
        return (Pair){
            mod_add(mod_mul(x, t.x, P), mod_mul(mod_mul(y, t.y, P), B, P), P),
            mod_add(mod_mul(x, t.y, P), mod_mul(y, t.x, P), P)
        };
    }
    Pair pow(LL k) {
        Pair ret = (Pair){1, 0}, tmp = *this;
        for( ; k > 0; k >>= 1, tmp = tmp * tmp)
            if(k & 1)
                ret = ret * tmp;
        return ret;
    }
};
LL mod_sqrt(LL x, LL p) {
    if(!x || p <= 2)
        return x;
    if(mod_pow(x, (p - 1) >> 1, p) != 1)
        return -1;
    LL w, y;
    do {
        w = randLL() % p;
        y = mod_sub(mod_mul(w, w, p), x, p);
    } while(mod_pow(y, (p - 1) >> 1, p) == 1);
    Pair A = (Pair){w, 1};
    B = y;
    P = p;
    A = A.pow((p + 1) >> 1);
    return A.x;
}
int t, n;
LL p, a[maxn];
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%I64d", &n, &p);
        if(p == 2) {
            for(int i = 0; i < n; ++i)
                scanf("%I64d", a + i);
            puts("0");
            continue;
        }
        std::map<LL, int> cnt;
        for(int i = 0; i < n; ++i) {
            scanf("%I64d", a + i);
            ++cnt[a[i]];
        }
        LL ans = 0, w = mod_sqrt(p - 3, p), x;
        LL w1 = mod_mul(mod_add(p - 1, w, p), (p + 1) >> 1, p);
        LL w2 = mod_mul(mod_sub(p - 1, w, p), (p + 1) >> 1, p);
        for(int i = 0; i < n; ++i) {
            --cnt[a[i]];
            if(!a[i])
                continue;
            x = mod_mul(a[i], w1, p);
            cnt.count(x) && (ans += cnt[x]);
            if(w1 == w2)
                continue;
            x = mod_mul(a[i], w2, p);
            cnt.count(x) && (ans += cnt[x]);
        }
        printf("%I64d\n", ans);
    }
    return 0;
}