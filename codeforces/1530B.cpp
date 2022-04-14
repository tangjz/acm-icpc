#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 21;

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);

    auto fill = [&](char buf[maxn][maxn]) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j)
                buf[i][j] = '0';
            buf[i][m] = '\0';
        }
    };
    int best = 0;
    static char ans[maxn][maxn];
    fill(ans);
    set<pair<int, int> > sp;
    sp.insert({0, 1});
    sp.insert({1, 0});
    sp.insert({0, m - 2});
    sp.insert({1, m - 1});
    sp.insert({n - 1, 1});
    sp.insert({n - 2, 0});
    sp.insert({n - 1, m - 2});
    sp.insert({n - 2, m - 1});
    vector<pair<int, int> > pos;
    for(auto &it: sp)
        pos.push_back(it);
    for(int msk = 0, sz = (int)pos.size(); msk < (1 << sz); ++msk) {
        int cnt = 0;
        static char tmp[maxn][maxn];
        fill(tmp);
        auto check = [&](int x, int y) {
            if(tmp[x][y] != '0')
                return;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    int xx = x + dx, yy = y + dy;
                    if(xx >= 0 && xx < n && yy >= 0 && yy < m && tmp[xx][yy] == '1') {
                        tmp[x][y] = '*';
                        return;
                    }
                }
            tmp[x][y] = '1';
            ++cnt;
        };
        bool skip = 0;
        for(int i = 0; !skip && i < sz; ++i)
            if((msk >> i) & 1) {
                check(pos[i].first, pos[i].second);
                skip |= tmp[pos[i].first][pos[i].second] != '1';
            } else {
                tmp[pos[i].first][pos[i].second] = '*';
            }
        if(skip)
            continue;
        for(int i = 0; i < m; ++i) {
            check(0, i);
            check(n - 1, i);
        }
        for(int i = 0; i < n; ++i) {
            check(i, 0);
            check(i, m - 1);
        }
        if(best < cnt) {
            best = cnt;
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < m; ++j)
                    if(tmp[i][j] == '*')
                        tmp[i][j] = '0';
                strcpy(ans[i], tmp[i]);
            }
        }
    }
    // fprintf(stderr, "best: %d\n", best);
    for(int i = 0; i < n; ++i)
        puts(ans[i]);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
        solve();
	}
	return 0;
}