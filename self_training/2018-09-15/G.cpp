#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, mod = (int)1e9 + 7;
int t;
char buf[maxn];
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%s", buf);
        int ex = 0;
        for(int i = 0; buf[i]; ++i)
            ex = (10LL * ex + buf[i] - '0') % (mod - 1);
        (--ex) < 0 && (ex += mod - 1);
        int ans = 1, tmp = 2;
        for( ; ex > 0; ex >>= 1, tmp = (LL)tmp * tmp % mod)
            (ex & 1) && (ans = (LL)ans * tmp % mod);
        printf("%d\n", ans);
	}
    return 0;
}