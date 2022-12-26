#include <bits/stdc++.h>
using namespace std;
const int maxn = 301, maxm = 501;

int t, n, m, tr[maxn][3];
unordered_map<string, int> Hash;
vector<pair<string, bool> > seq;
vector<pair<double, bool> > dp[maxm][maxm];

inline void upd(pair<double, bool> const &lft, pair<double, bool> const &rht, pair<double, bool> &ret) {
    if(!lft.second || !rht.second)
        return;
    double val = lft.first + rht.first;
    if(!ret.second) {
        ret.first = val;
        ret.second = true;
    } else if(ret.first < val) {
        ret.first = val;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < 3; ++j) {
            int &idx = tr[i][j];
            string cur;
            cin >> cur;
            auto it = Hash.find(cur);
            if(it != Hash.end()) {
                idx = it -> second;
            } else {
                idx = (int)seq.size();
                Hash.insert({cur, idx});
                seq.push_back({cur, false});
            }
            seq[idx].second |= j < 2;
        }
    cin >> t;
    while(t--) {
        cin >> m;
        for(int i = 0; i < m; ++i) {
            for(int j = i; j < m; ++j)
                vector<pair<double, bool> >(seq.size()).swap(dp[i][j]);
            string cur;
            double prb;
            cin >> cur;
            while(cur != "END") {
                cin >> prb;
                auto it = Hash.find(cur);
                if(it != Hash.end()) {
                    int idx = it -> second;
                    if(m == 1 || seq[idx].second)
                        dp[i][i][idx] = {log(prb), true};
                }
                cin >> cur;
            }
        }
        for(int len = 2; len <= m; ++len)
            for(int L = 0, R = len - 1; R < m; ++L, ++R)
                for(int M = L; M < R; ++M)
                    for(int i = 0; i < n; ++i) {
                        int u = tr[i][0], v = tr[i][1], w = tr[i][2];
                        if(len < m && !seq[w].second)
                            continue;
                        upd(dp[L][M][u], dp[M + 1][R][v], dp[L][R][w]);
                        upd(dp[L][M][v], dp[M + 1][R][u], dp[L][R][w]);
                    }
        int best = -1;
        auto &vec = dp[0][m - 1];
        for(int i = 0; i < (int)seq.size(); ++i)
            if(vec[i].second && (best == -1 || vec[best].first < vec[i].first))
                best = i;
        cout << (best == -1 ? "GAMEOVER" : seq[best].first) << endl;
    }
    return 0;
}
