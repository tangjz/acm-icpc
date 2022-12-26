#include <cstdio>
int main() {
    int t, n, m, p;
    scanf("%d", &t);
    while(t--) {
        long long ans = 0;
        scanf("%d%d%d", &n, &m, &p);
        for(int rem = n * m - 1, ctr; rem > 0; rem -= ctr) {
            ctr = (rem - 1) / p + 1;
            if(ctr == 1)
                break;
            ans += ((ctr * (ctr - 1)) >> 1) * (p - 1LL);
        }
        puts(!(ans & 1) ? "YES" : "NO");
    }
    return 0;
}
