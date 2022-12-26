#include <cstdio>
typedef long long LL;
const int maxn = 19, maxm = 173, mod = (int)1e9 + 9;
int t;
LL n, pw[maxn];
struct Info {
    LL cnt, nxt;
    int sum;
} f[maxn][maxm][maxm];
bool vis[maxn][maxm][maxm];
inline int digitSum(LL x) {
    int ret = 0;
    for( ; x; ret += x % 10, x /= 10);
    return ret;
}
Info &F(int len, int pre, int suf) {
    Info &ret = f[len][pre][suf];
    if(!len || vis[len][pre][suf])
        return ret;
    vis[len][pre][suf] = 1;
    ret.nxt = suf;
    while(1) { // at most 10 times
        LL tmp = ret.nxt / pw[len - 1], adt = tmp * pw[len - 1];
        Info &cur = F(len - 1, pre + digitSum(tmp), ret.nxt - adt);
        ret.cnt += cur.cnt;
        ret.nxt = cur.nxt + adt;
        ret.sum = (ret.sum + cur.sum + cur.cnt % mod * (adt % mod)) % mod;
        tmp = ret.nxt + digitSum(ret.nxt) + pre;
        if(tmp >= pw[len])
            break;
        ++ret.cnt;
        ret.nxt = tmp;
        ret.sum = (ret.sum + ret.nxt) % mod;
    }
    return ret;
}
int main() {
    pw[0] = 1;
    for(int i = 1; i < maxn; ++i)
        pw[i] = pw[i - 1] * 10;
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        scanf("%lld", &n);
        Info ret = (Info){1, 1, 1};
        for(int len = maxn - 1; len > 0; --len)
            while(1) { // at most 10 times
                LL tmp = ret.nxt / pw[len], adt = tmp * pw[len];
                Info &cur = F(len, digitSum(tmp), ret.nxt - adt);
                if(ret.cnt + cur.cnt + 1 > n)
                    break;
                ret.cnt += cur.cnt + 1;
                ret.nxt = cur.nxt + adt;
                ret.nxt += digitSum(ret.nxt);
                ret.sum = (ret.sum + cur.sum + cur.cnt % mod * (adt % mod) + ret.nxt) % mod;
            }
        while(ret.cnt < n) {
            ++ret.cnt;
            ret.nxt += digitSum(ret.nxt);
            ret.sum = (ret.sum + ret.nxt) % mod;
        }
        printf("Case #%d: %lld %d\n", Case, ret.nxt, ret.sum);
    }
    return 0;
}
