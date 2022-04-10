#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
const int maxn = (int)2e5 + 9, maxm = (int)1e6 + 9, maxd = 26;
const int mod = (int)1e9 + 7;
const DB eps = (DB)1e-12, pi = acos((DB)-1);

inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int> > pos(n + 1);
    int cand = 0;
    for(int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        if(pos[x].size() < m) {
            pos[x].push_back(i);
            ++cand;
        }
    }
    cand /= m;
    // printf("cand: %d\n", cand);
    vector<int> ans(n), ord(n + 1);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
        return pos[u].size() > pos[v].size();
    });
    queue<pair<int, int> > que;
    for(int i = 1; i <= m; ++i)
        que.push({i, cand});
    for(int i: ord)
        for(int k: pos[i]) {
            if(que.empty())
                break;
            pair<int, int> tmp = que.front();
            que.pop();
            ans[k] = tmp.first;
            --tmp.second;
            if(tmp.second > 0)
                que.push(tmp);
        }
    for(int i = 0; i < n; ++i)
        printf("%d%c", ans[i], " \n"[i == n - 1]);
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: %d\n", Case, solve());
        solve();
    }
    return 0;
}