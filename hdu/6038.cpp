#include <cstdio>
const int maxn = 100001, mod = 1000000007;
int n, m, a[maxn], b[maxn], c[maxn], ans;
int main() {
    for(int Case = 1; scanf("%d%d", &n, &m) == 2; ++Case) {
        for(int i = 0; i < n; ++i)
            scanf("%d", a + i);
        for(int i = 0; i < m; ++i) {
            scanf("%d", b + i);
            c[i + 1] = 0;
        }
        for(int i = 0; i < m; ++i) {
            if(b[i] == -1)
                continue;
            int cnt = 0;
            for(int j = i, k = b[i]; b[k] != -1; j = k, k = b[k], b[j] = -1, ++cnt);
            c[cnt] += cnt;
        }
        ans = 1;
        for(int i = 0; i < n; ++i) {
            if(a[i] == -1)
                continue;
            int cnt = 0, sum = 0;
            for(int j = i, k = a[i]; a[k] != -1; j = k, k = a[k], a[j] = -1, ++cnt);
            for(int j = 1; j <= m && j * j <= cnt; ++j)
                if(cnt % j == 0) {
                    sum += c[j];
                    if(j * j < cnt && cnt / j <= m)
                        sum += c[cnt / j];
                }
            ans = (long long)ans * sum % mod;
        }
        printf("Case #%d: %d\n", Case, ans);
    }
    return 0;
}
