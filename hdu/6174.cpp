#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn = 100001, mod = (int)1e9 + 7;
int inv[maxn + 2], t, n, p[maxn], v[maxn], f[maxn], ans;
vector<int> e[maxn];
void dfs(int x, int z) {
    f[x] = 1;
    for(vector<int>::iterator it = e[x].begin(); it != e[x].end(); ++it) {
        int y = *it;
        if(y != z && v[y] != -1) {
            dfs(y, x);
            f[x] += f[y];
        }
    }
}
int main() {
    inv[1] = 1;
    for(int i = 2; i <= maxn; ++i)
        inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i)
            vector<int>().swap(e[i]);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", p + i);
            e[p[i]].push_back(i);
        }
        ans = n + 1;
        memset(v + 1, 0, n * sizeof(int));
        for(int i = 1, j, k, c; i <= n; ++i) {
            if(!v[i]) {
                for(j = i; !v[j]; v[j] = i, j = p[j]);
                if(v[j] == i) {
                    for(v[j] = -1, k = p[j]; k != j; v[k] = -1, k = p[k]);
                    for(dfs(j, -1), c = f[j], k = p[j]; k != j; dfs(k, -1), c += f[k], k = p[k]);
                    for(f[j] = c, k = p[j]; k != j; f[k] = c, k = p[k]);
                }
            }
            (ans -= inv[f[i] + 1]) < 0 && (ans += mod);
        }
        printf("%d\n", ans);
    }
    return 0;
}