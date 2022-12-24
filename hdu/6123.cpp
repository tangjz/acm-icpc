#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 60001;
int t, n, m, deg[maxn], ord[maxn], coeff[maxn];
vector<int> e[maxn];
bool vis[maxn];
inline bool cmp(int const &x, int const &y) {
    return deg[x] < deg[y] || (deg[x] == deg[y] && x < y);
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        memset(deg + 1, 0, ((n + 1) >> 1) * sizeof(int));
        for(int i = 1; i <= (n + 1) >> 1; ++i) {
            vector<int>().swap(e[i]);
            ord[i] = i;
            coeff[i] = 2;
        }
        coeff[(n + 1) >> 1] -= n & 1;
        while(m--) {
            int u, v;
            scanf("%d%d", &u, &v);
            ++deg[u];
            e[u].push_back(v);
            if(u != v) {
                ++deg[v];
                e[v].push_back(u);
            }
        }
        sort(ord + 1, ord + ((n + 1) >> 1) + 1, cmp);
        LL ans = (LL)n * n * n; // 0
        for(int i = (n + 1) >> 1; i >= 1; --i) {
            int u = ord[i], way1 = coeff[u], sum = 0;
            if(!deg[u])
                break;
            for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
                int v = *it;
                sum += coeff[v];
                if(cmp(u, v))
                    continue;
                vis[v] = 1;
            }
            // printf("%d: %I64d\n", u, (LL)sum * (n - sum) * way1 * 3);
            ans -= (LL)sum * (n - sum) * way1 * 3; // 1, 2
            for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
                int v = *it;
                if(cmp(u, v))
                    continue;
                int way2 = way1 * coeff[v], cnt = 3;
                u != v && (way2 *= cnt--);
                for(vector<int>::iterator jt = e[v].begin(); jt != e[v].end(); ++jt) {
                    int w = *jt;
                    if(cmp(v, w) || !vis[w])
                        continue;
                    // printf("%d %d %d: %d\n", u, v, w, v != w ? way2 * coeff[w] * cnt : way2 * coeff[w]);
                    ans -= v != w ? way2 * coeff[w] * cnt : way2 * coeff[w]; // 3
                }
            }
            for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
                int v = *it;
                if(cmp(u, v))
                    continue;
                vis[v] = 0;
            }
        }
        printf("%I64d\n", ans);
    }
    return 0;
}