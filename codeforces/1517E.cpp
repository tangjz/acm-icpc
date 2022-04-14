#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL solve() {
    const int maxn = (int)2e5 + 1;
    int n;
    static int a[maxn];
    static LL s[maxn], s2[maxn];
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        s[i] = (i - 1 >= 0 ? s[i - 1] : 0) + a[i];
        s2[i] = (i - 2 >= 0 ? s2[i - 2] : 0) + a[i];
    }
    LL ans = 0;
    // P_2 C_0 [P_1 C_1] P_0 C_2
    for(int has_lft = 0; has_lft < 2; ++has_lft)
        for(int has_rht = 0; has_rht < 2; ++has_rht) {
            int lft_low = has_lft ? 2 : 0;
            int rht_low = has_rht ? 2 : 0;
            int least = has_lft + lft_low + rht_low + has_rht;
            if(least > n)
                continue;
            auto check = [&](int cL, int cM, int cR) {
                int pos = 0;
                LL sum_c = 0, sum_p = 0;
                // printf("sum %d: %d %d %d %d %d: ", has_lft + has_rht + cL + cM + cR, has_lft, cL, cM, cR, has_rht);
                if(has_lft)
                    sum_p += a[pos++];
                if(cL) {
                    sum_c += s[pos + cL - 1] - (pos - 1 >= 0 ? s[pos - 1] : 0);
                    pos += cL;
                }
                if(cM) {
                    sum_p += s2[pos + cM - 2] - (pos - 2 >= 0 ? s2[pos - 2] : 0);
                    sum_c += s2[pos + cM - 1] - (pos - 1 >= 0 ? s2[pos - 1] : 0);
                    pos += cM;
                }
                if(cR) {
                    sum_p += s[pos + cR - 1] - (pos - 1 >= 0 ? s[pos - 1] : 0);
                    pos += cR;
                }
                if(has_rht)
                    sum_c += a[pos++];
                assert(pos == n);
                // printf("%d (%lld %lld)\n", sum_c < sum_p, sum_c, sum_p);
                return sum_c < sum_p;
            };
            for(int cL = lft_low, cM = (n - least) / 2 * 2, cR = n - has_lft - has_rht - cL - cM; cL <= n; cL += 2) {
                while(cR < rht_low || (cM >= 0 && !check(cL, cM, cR))) {
                    cR += 2;
                    cM -= 2;
                }
                if(cM >= 0)
                    ans += cM / 2 + 1;
                cR -= 2;
            }
            if(least + 1 > n)
                continue;
            for(int cL = lft_low + 1, cM = (n - least - 1) / 2 * 2, cR = n - has_lft - has_rht - cL - cM; cL <= n; cL += 2) {
                while(cR < rht_low || (cM >= 0 && !check(cL, cM, cR))) {
                    cR += 2;
                    cM -= 2;
                }
                if(cM >= 0)
                    ans += cM / 2 + 1;
                cR -= 2;
            }
        }
    // P_0 P_0 C_0 C_0
    LL sum_p = a[0], sum_c = s[n - 1] - sum_p;
    for(int i = 2; i < n - 1; ++i) {
        sum_p += a[i - 1];
        sum_c -= a[i - 1];
        ans += sum_p > sum_c;
    }
    return ans;
}
int main() {
    const int mod = 998244353;
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		printf("%lld\n", solve() % mod);
	}
	return 0;
}