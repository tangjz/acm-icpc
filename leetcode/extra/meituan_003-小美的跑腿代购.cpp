#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1;

int main() {
    int n, m;
    static pair<int, int> a[maxn];
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        a[i] = {-x - y - y, i};
    }
    m = min(m, n);
    nth_element(a, a + m, a + n);
    static bool vis[maxn] = {};
    for(int i = 0; i < m; ++i)
        vis[a[i].second] = 1;
    for(int i = 0, fir = 1; i < n; ++i) {
        if(!vis[i])
            continue;
        if(fir) {
            fir = 0;
        } else {
            putchar(' ');
        }
        printf("%d", i + 1);
    }
    putchar('\n');
    return 0;
}
