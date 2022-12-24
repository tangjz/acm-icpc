#include <bits/stdc++.h>
typedef unsigned long long ULL;
const int maxn = 100001;
int t, n, m;
struct Node {
    ULL HP, AP;
    bool operator < (Node const &t) const {
        return HP * t.AP < AP * t.HP;
    }
} a[maxn], b[maxn];
__int128_t evaluate(int n, Node a[]) {
    __int128_t ret = 0, sum = 0;
    std::sort(a, a + n);
    for(int i = 0; i < n; ++i) {
        sum += a[i].HP;
        ret += sum * a[i].AP;
    }
    return ret;
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i)
            scanf("%llu", &a[i].HP);
        for(int i = 0; i < n; ++i)
            scanf("%llu", &a[i].AP);
        for(int i = 0; i < m; ++i)
            scanf("%llu", &b[i].HP);
        for(int i = 0; i < m; ++i)
            scanf("%llu", &b[i].AP);
        __int128_t diff = evaluate(n, a) - evaluate(m, b);
        puts(diff ? (diff > 0 ? "Units win" : "Towers win") : "Tie");
    }
    return 0;
}