#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)4e4 + 1;

int main() {
    int n, x, y;
    static int a[maxn], ord[maxn];
    static char buf[maxn];
    scanf("%d%d", &x, &y);
    n = x + y;
    for(int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        ord[i] = i;
    }
    if(x != y) {
        int sgn = x < y ? -1 : 1;
        sort(ord, ord + n, [&](int const &u, int const &v) {
            return make_pair(a[u], sgn * u) < make_pair(a[v], sgn * v);
        });
    }
    buf[n] = '\0';
    if(x < y) {
        while(x--)
            buf[ord[--n]] = 'A';
        while(y--)
            buf[ord[--n]] = 'B';
    } else {
        while(y--)
            buf[ord[--n]] = 'B';
        while(x--)
            buf[ord[--n]] = 'A';
    }
    puts(buf);
    return 0;
}
