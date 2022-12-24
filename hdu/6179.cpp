#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 3001, maxv = 201, maxs = 48929;
int Gcd[maxv][maxv], tot, idx[maxv << 1 | 1][maxv], t, n, rk[maxn], ord[maxn], ans[maxs];
pair<int, int> vec[maxs], p[maxn], ori;
vector<pair<int, int> > event[maxs];
bool cmp(pair<int, int> const &u, pair<int, int> const &v) {
    return u.first * v.second - v.first * u.second > 0;
}
int main() {
    for(int i = 1; i < maxv; ++i)
        Gcd[0][i] = Gcd[i][0] = i;
    vec[tot++] = make_pair(1, 0);
    for(int i = 1; i < maxv; ++i)
        for(int j = 1; j < maxv; ++j) {
            Gcd[i][j] = i <= j ? Gcd[i][j - i] : Gcd[j][i];
            if(Gcd[i][j] == 1)
                vec[tot++] = make_pair(i, j);
        }
    sort(vec, vec + tot, cmp);
    for(int i = 0; i < tot; ++i)
        vec[tot + i] = make_pair(-vec[i].second, vec[i].first);
    tot <<= 1;
    for(int i = 0; i < tot; ++i)
        idx[maxv + vec[i].first][vec[i].second] = i;
    ori = make_pair(0, 0);
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
            scanf("%d%d", &p[i].first, &p[i].second);
        sort(p, p + n);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < i; ++j) {
                int dx = p[j].first - p[i].first, dy = p[j].second - p[i].second;
                if(dx < 0 || (!dx && dy < 0)) {
                    dx = -dx;
                    dy = -dy;
                }
                int r = Gcd[dx][abs(dy)];
                event[idx[maxv - dy / r][dx / r]].push_back(make_pair(j, i));
            }
        int cnt = 0, len = 0, sz = 0;
        static int tmp[maxs];
        for(int i = 0; i < n; ++i) {
            cnt += p[i] < ori;
            rk[i] = ord[i] = i;
        }
        ans[len++] = ord[cnt];
        tmp[sz++] = ord[n - 1 - cnt];
        for(int i = 0; i < tot; ++i) {
            if(!event[i].size())
                continue;
            for(vector<pair<int, int> >::iterator it = event[i].begin(); it != event[i].end(); ++it) {
                int u = it -> first, v = it -> second;
                if((p[u].first - p[v].first) * vec[i].second <= 0 && vec[i].first * (p[u].second - p[v].second) >= 0) {
                    swap(rk[u], rk[v]);
                    swap(ord[rk[u]], ord[rk[v]]);
                }
            }
            if(ans[len - 1] != ord[cnt])
                ans[len++] = ord[cnt];
            if(tmp[sz - 1] != ord[n - 1 - cnt])
                tmp[sz++] = ord[n - 1 - cnt];
            vector<pair<int, int> >().swap(event[i]);
        }
        for(int i = ans[len - 1] == tmp[0]; i < sz; ++i)
            ans[len++] = tmp[i];
        len -= ans[0] == ans[len - 1];
        scanf("%d", &n);
        while(n--) {
            int id;
            scanf("%d", &id);
            id %= len;
            printf("%d %d\n", p[ans[id]].first, p[ans[id]].second);
        }
    }
    return 0;
}