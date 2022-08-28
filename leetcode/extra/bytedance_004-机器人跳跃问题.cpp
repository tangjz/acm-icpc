#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
    int n, x, low = 0;
    LL rem = 0, mod = 1;
    scanf("%d", &n);
    LL upp = n * (LL)2e5 + 1;
    while(n--) {
        if(mod > upp) {
            rem = 1;
            break;
        }
        scanf("%d", &x);
        rem = rem * 2 + x;
        mod *= 2;
        low += rem / mod;
        rem %= mod;
    }
    printf("%d\n", low + (rem > 0));
    return 0;
}
