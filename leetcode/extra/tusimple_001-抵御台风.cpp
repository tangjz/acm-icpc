#include <bits/stdc++.h>
using namespace std;

const int maxr = 1001, maxc = 11, maxn = (int)1e4 + 1;

int main() {
    int r, c, nL = 0, nU = 0, ans = 0;
    static char buf[maxr][maxc];
    static int pL[maxr][maxc], pU[maxr][maxc];
    scanf("%d%d", &r, &c);
    for(int i = 0; i < r; ++i) {
        scanf("%s", buf[i]);
        for(int j = 0; j < c; ++j) {
            pL[i][j] = pU[i][j] = -1;
            if(buf[i][j] != '#')
                continue;
            ++ans;
            if(j > 0 && buf[i][j - 1] == '#') {
                pL[i][j] = nL++;
                --ans;
            }
            if(i > 0 && buf[i - 1][j] == '#') {
                pU[i][j] = nU++;
                --ans;
            }
        }
    }

    static int match[maxn];
    static bool vis[maxn];
    static vector<int> e[maxn];
    for(int i = 0; i < nL; ++i)
        e[i].clear();
    memset(match, -1, nU * sizeof(int));
    for(int i = 0; i < r; ++i)
        for(int j = 0; j < c; ++j) {
            if(buf[i][j] != '#')
                continue;
            vector<int> cand;
            if(pU[i][j] != -1)
                cand.push_back(pU[i][j]);
            if(i + 1 < r && pU[i + 1][j] != -1)
                cand.push_back(pU[i + 1][j]);
            if(cand.empty())
                continue;
            int u = pL[i][j];
            if(u != -1)
                e[u].insert(e[u].begin(), cand.begin(), cand.end());
            if(j + 1 < c && (u = pL[i][j + 1]) != -1)
                e[u].insert(e[u].begin(), cand.begin(), cand.end());
        }
    function<bool(int)> path = [&](int u) {
        for(int v: e[u]) {
            if(vis[v])
                continue;
            vis[v] = 1;
            if(match[v] == -1 || path(match[v])) {
                match[v] = u;
                return 1;
            }
        }
        return 0;
    };
    for(int i = 0; i < nL; ++i) {
        memset(vis, 0, nU * sizeof(bool));
        if(path(i))
            ++ans;
    }
    printf("%d\n", ans);
    return 0;
}
