#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline LL sum1(LL n) { // sum(i)
    return n * (n + 1) / 2;
}
inline LL sum2(LL n) { // sum(i * i)
    return n * (n + 1) * (n + n + 1) / 6;
}
inline LL sum3(LL n) { // sum(i * (i + 1))
    return n * (n + 1) * (n + 2) / 3;
}
LL getCnt(int u, int v) {
    LL ret = sum1(u) * 4 + 1;
    int u1 = u - (v + 1);
    if(u1 >= 0) {
        LL tmp = sum1(u1) * 4 + (u1 + 1LL) * 2;
        ret -= tmp * 2;
        int u2 = u1 - (v + 1);
        if(u2 >= 0) {
            ret += sum1(u2 + 1) * 4;
        }
    }
    return ret;
}
LL getSum(int u, int v) {
    LL ret = sum2(u) * 4;
    int u1 = u - (v + 1);
    if(u1 >= 0) {
        LL tmp = sum1(u1) * 4 + (u1 + 1LL) * 2;
        tmp = tmp * (v + 1) + sum2(u1) * 4 + sum1(u1) * 2;
        ret -= tmp * 2;
        int u2 = u1 - (v + 1);
        if(u2 >= 0) {
            LL tmp = sum1(u2 + 1) * 4;
            tmp = tmp * (v + 1) * 2 + sum3(u2) * 4;
            ret += tmp;
        }
    }
    return ret;
}
const int maxd = 5, maxv = (int)2e9;
int sz[maxd];
LL getCnt(LL upp) {
    // printf("cnt %lld:", upp);
    LL ret = 0;
    for(int i = 1; i < maxd; ++i) {
        int prd = maxd - i;
        int u = (int)min(upp / prd, (LL)maxv);
        // LL las = ret;
        ret += getCnt(u, sz[i]);
        if(i > 1)
            ret -= getCnt(u, sz[i - 1]);
        // printf(" %lld", ret - las);
    }
    // puts("");
    return ret;
}
LL getSum(LL upp) {
    // printf("sum %lld:", upp);
    LL ret = 0;
    for(int i = 1; i < maxd; ++i) {
        int prd = maxd - i;
        int u = (int)min(upp / prd, (LL)maxv);
        // LL las = ret;
        ret += getSum(u, sz[i]) * prd;
        if(i > 1)
            ret -= getSum(u, sz[i - 1]) * prd;
        // printf(" %lld", ret - las);
    }
    // puts("");
    return ret;
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        sz[0] = -1;
        for(int i = 1; i < maxd; ++i)
            scanf("%d", sz + i);
        LL cnt;
        scanf("%lld", &cnt);
        if(cnt <= 1) {
            puts("0");
            continue;
        }
        LL L = 0, R = sz[maxd - 1] * 8LL;
        while(L < R) {
            LL M = (L + R) >> 1;
            if(getCnt(M) < cnt) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        // assert(L > 0);
        LL rem = cnt - getCnt(L - 1);
        LL ans = getSum(L - 1) + rem * L;
        printf("%lld\n", ans);
    }
    return 0;
}
