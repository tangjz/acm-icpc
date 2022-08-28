#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1;

typedef long long LL;

void solve() {
    int n;
    static int a[maxn];
    LL sum = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        sum += a[i];
    }
    if(sum & 1) {
        puts("NO");
        return;
    }
    sum >>= 1;
    for(int i = 0, j = 0; i < n; ++i) {
        for( ; j < n && sum >= a[j]; sum -= a[j++]);
        if(!sum) {
            puts("YES");
            return;
        }
        sum += a[i];
    }
    puts("NO");
}

int main() {
    int T;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case)
        solve();
    return 0;
}
