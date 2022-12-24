#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 240001;
int t, cir, c[4];
LL k, dis[maxn], ans;
bool vis[maxn];
priority_queue<pair<LL, int> > Q;
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%I64d", &k);
        for(int i = 0; i < 4; ++i)
            scanf("%d", c + i);
        cir = min(c[0], c[1]) << 1;
        memset(dis, 0x3f, (cir << 2) * sizeof(LL));
        memset(vis, 0, (cir << 2) * sizeof(bool));
        dis[1] = 0;
        Q.push(make_pair(0LL, 1));
        while(!Q.empty()) {
            int u = Q.top().second;
            Q.pop();
            if(vis[u])
                continue;
            int uL = u >> 2, uR = u & 3;
            { // case 1
                int vR = (uR + 1) & 3, vL = (uL + c[uR]) % cir, v = vL << 2 | vR;
                LL tmp = dis[u] + c[uR];
                if(tmp < dis[v]) {
                    dis[v] = tmp;
                    Q.push(make_pair(-dis[v], v));
                }
            }
            { // case 2
                int vR = (uR + 3) & 3, vL = (uL + c[vR]) % cir, v = vL << 2 | vR;
                LL tmp = dis[u] + c[vR];
                if(tmp < dis[v]) {
                    dis[v] = tmp;
                    Q.push(make_pair(-dis[v], v));
                }
            }
        }
        ans = 0x3f3f3f3f3f3f3f3fLL;
        for(int i = 0; i < cir; ++i) {
            LL tmp = dis[i << 2 | 1];
            if(tmp < k)
                tmp += ((k - tmp - 1) / cir + 1) * cir;
            if(tmp < ans)
                ans = tmp;
        }
        printf("%I64d\n", ans);
    }
    return 0;
}