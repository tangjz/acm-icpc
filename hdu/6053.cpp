#include <cstdio>
#include <algorithm>
using namespace std;
namespace fastIO {
    #define BUF_SIZE 100001
    //fread -> read
    bool IOerror = 0;
    inline char nc() {
        static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
        if(p1 == pend) {
            p1 = buf;
            pend = buf + fread(buf, 1, BUF_SIZE, stdin);
            if(pend == p1) {
                IOerror = 1;
                return -1;
            }
        }
        return *p1++;
    }
    inline bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }
    inline void read(int &x) {
        char ch;
        while(blank(ch = nc()));
        if(IOerror)
            return;
        for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
    }
    #undef BUF_SIZE
} using namespace fastIO;
typedef long long LL;
const int maxn = 100001, mod = 1000000007;
int mu[maxn], t, n, a[maxn], s[maxn];
int mod_pow(int x, int k) {
    int ret = 1;
    for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
        (k & 1) && (ret = (LL)ret * x % mod);
    return ret;
}
int main() {
    mu[1] = 1;
    for(int i = 1; i < maxn; ++i)
        for(int j = i + i; j < maxn; j += i)
            mu[j] -= mu[i];
    read(t);
    for(int Case = 1; Case <= t; ++Case) {
        read(n);
        int mn = maxn, mx = 0;
        for(int i = 0; i < n; ++i) {
            read(a[i]);
            mn = min(mn, a[i]);
            mx = max(mx, a[i]);
        }
        for(int i = 1; i <= mx; ++i)
            s[i] = 0;
        for(int i = 0; i < n; ++i)
            ++s[a[i]];
        for(int i = 1; i <= mx; ++i)
            s[i] += s[i - 1];
        int ans = 0;
        for(int i = 2; i <= mn; ++i) {
            if(!mu[i])
                continue;
            int prd = 1;
            for(int o = 1, j = i; j <= mx; ++o, j += i) {
                int k = min(j + i - 1, mx), cnt = s[k] - s[j - 1];
                if(cnt)
                    prd = (LL)prd * mod_pow(o, cnt) % mod;
            }
            if(mu[i] > 0)
                (ans -= prd) < 0 && (ans += mod);
            else if(mu[i] < 0)
                (ans += prd) >= mod && (ans -= mod);
        }
        printf("Case #%d: %d\n", Case, ans);
    }
    return 0;
}