#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1;

void solve() {
    int n;
    static int ord[maxn];
    static pair<int, int> a[maxn];
	scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        int hh, mm;
        scanf("%d:%d", &hh, &mm);
        a[i].second = hh * 60 + mm;
        scanf("%d:%d", &hh, &mm);
        a[i].first = hh * 60 + mm;
        ord[i] = i;
    }
    sort(ord, ord + n, [&](int const &u, int const &v) {
        return a[u] < a[v];
    });
    int m = 0;
    static int pos[maxn];
    for(int i = 0, las = -1; i < n; ++i) {
        int u = ord[i];
        if(las <= a[u].second) {
            pos[m++] = u;
            las = a[u].first;
        }
    }
    sort(pos, pos + m, [&](int const &u, int const &v) {
        return a[u].second < a[v].second;
    });
    for(int i = 0; i < m; ++i)
        printf("%d%c", pos[i] + 1, " \n"[i == m - 1]);
}

int main() {
    int T = 1;
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
