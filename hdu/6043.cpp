#include <cstdio>
int n;
long long k;
int main() {
    for(int Case = 1; scanf("%d%I64d", &n, &k) == 2; ++Case)
        if(k <= n) {
            printf("Case #%d: %d\n", Case, (int)k);
        } else {
            k = (k - n) % ((n - 1) << 1);
            if(!k) {
                printf("Case #%d: %d\n", Case, n);
            } else {
                printf("Case #%d: %d\n", Case, (int)((k - 1) % (n - 1) + 1));
            }
        }
    return 0;
}
