#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int t, mx;
LL n, lim, ans;
LL solve(LL sta, LL stp, LL len) {
    LL ret = 0, end = sta + (len - 1) * stp;
    for(LL i = 1; i <= end; i <<= 1) {
        LL a = stp, b = sta, c = i, n = len, ctr = 0;
        while(n) {
            LL u = a / c, v = b / c;
            ctr ^= (((n & 2) ? u : 0) + ((n & 1) ? v : 0)) & 1;
            a -= u * c;
            b = a * n + b - v * c;
            n = b / c;
            b -= n * c;
            swap(a, c);
        }
        if(ctr)
            ret |= i;
    }
    return ret;
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%lld", &n);
        for(mx = 1; 1LL << mx <= n; ++mx);
        lim = max(sqrtl(n) / mx, (long double)0);
        ans = 0;
        for(LL i = 0, j, k; i < n; i = j) {
            k = n / (i + 1);
            j = n / k;
            if(k <= lim) {
                ans ^= solve(n - j * k, k, j - i);
            } else {
                for(LL x = n - j * k, y = n - i * k; x < y; x += k)
                    ans ^= x;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}