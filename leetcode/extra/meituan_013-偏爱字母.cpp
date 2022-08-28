#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)3e5 + 1;

int main() {
    int n, ans = 0, pre = 0;
    static char buf[maxn];
    scanf("%d%s", &n, buf);
    for(int i = 0; i < n; ++i) {
        pre = max(pre, 0) + (buf[i] == 'E' ? 1 : (buf[i] == 'F' ? -1 : 0));
        ans = max(ans, pre);
    }
    printf("%d\n", ans);
    return 0;
}
