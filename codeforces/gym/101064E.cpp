#include <bits/stdc++.h>
using namespace std;

const int maxn = 15, maxl = 301, maxc = 10, maxs = (int)1e7 + 1;

int tot, msk[maxl], sub[maxl][maxc + 1];
int f[maxl], nxt[maxl][maxc + 1];
vector<pair<int, char> > e[maxl];
int que[maxs], dis[maxs];
pair<int, char> pre[maxs];

inline int newNode() {
    msk[tot] = 0;
    memset(sub[tot], 0, maxc * sizeof(int));
    return tot++;
}

void solve() {
    int n, m;
    static char buf[maxl];
    scanf("%d%d", &n, &m);
    tot = 0;
    newNode();
    for(int i = 0; i < n + m; ++i) {
        scanf("%s", buf);
        int rt = 0;
        for(int j = 0; buf[j]; ++j) {
            int o = buf[j] - 'a';
            if(!sub[rt][o])
                sub[rt][o] = newNode();
            rt = sub[rt][o];
        }
        msk[rt] |= 1 << i;
    }
    que[0] = 0;
    f[0] = 0;
    memcpy(nxt[0], sub[0], maxc * sizeof(int));
    for(int i = 0, sz = 1; i < sz; ++i) {
        int u = que[i];
        e[u].resize(maxc);
        for(int j = 0; j < maxc; ++j) {
            int v = sub[u][j];
            if(!v) {
                nxt[u][j] = nxt[f[u]][j];
            } else {
                f[v] = u ? nxt[f[u]][j] : 0;
                msk[v] |= msk[f[v]];
                nxt[u][j] = v;
                que[sz++] = v;
            }
            e[u][j] = {nxt[u][j], 'a' + j};
        }
        sort(e[u].begin(), e[u].end());
        e[u].erase(unique(e[u].begin(), e[u].end(), [&](auto const &u, auto const &v) {
            return u.first == v.first;
        }), e[u].end());
    }
    memset(dis, -1, (tot << n) * sizeof(int));
    que[0] = 0;
    dis[0] = 0;
    int all = (1 << n) - 1;
    for(int i = 0, sz = 1; i < sz; ++i) {
        int u = que[i], uPos = u >> n, uMsk = u & all;
        for(auto &it: e[uPos]) {
            int vPos = it.first, vMsk = uMsk | msk[vPos];
            int v = vPos << n | vMsk;
            if(vMsk > all || dis[v] != -1)
                continue;
            dis[v] = dis[u] + 1;
            que[sz] = v;
            pre[sz] = {i, it.second};
            if(vMsk == all) {
                static char out[(maxl * maxn + 1) | 1];
                int len = 0;
                while(sz > 0) {
                    out[len++] = pre[sz].second;
                    sz = pre[sz].first;
                }
                reverse(out, out + len);
                out[len] = '\0';
                puts(out);
                return;
            }
            ++sz;
        }
    }
    puts("-");
}

int main() {
    int T = 1;
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
