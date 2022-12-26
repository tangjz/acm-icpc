#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int maxn = 63, mod = (int)1e9 + 7;

inline void modInc(int &x, int y) {
    (x += y) >= mod && (x -= mod);
}

void solve() {
    int n;
    scanf("%d", &n);
    unordered_map<int, int> f = {{0, 1}};
    for(int i = 1; i <= n; ++i) {
        int ways = 0, prd = 1;
        for(int j = 1; j <= 4 && j <= i; ++j) {
            prd = prd * (i - j + 1) / j;
            ways += prd;
        }
        unordered_map<int, int> g(ways + ways / 2);
        for(auto &it: f) {
            int adt = 0;
            vector<int> vals;
            // printf("%d |", i - 1);
            for(int tmp = it.first; tmp > 0; tmp >>= 6) {
                adt = adt << 6 | 1;
                vals.push_back(tmp & 63);
                // printf(" %d", vals.back());
            }
            // printf(" : %d\n", it.second);
            int m = vals.size(), base = 1;
            for(int o = 0; o < m; ++o, base <<= 6) {
                adt -= base;
                int L = o ? vals[o - 1] + 1 : 1, R = vals[o];
                for(int j = R, msk = it.first + adt; j >= L; --j, msk -= base) {
                    modInc(g[msk], it.second);
                }
            }
            if(vals.size() == 4)
                continue;
            for(int j = m ? vals.back() + 1 : 1, msk = it.first + base * j; j <= i; ++j, msk += base)
                modInc(g[msk], it.second);
        }
        f = move(g);
    }
    int ans = 1;
    for(int i = 1; i <= n; ++i)
        ans = (i64)ans * i % mod;
    for(auto &it: f) {
        int m = 0;
        // printf("%d |", n);
        for(int tmp = it.first; tmp > 0; ++m, tmp >>= 6) {
            // printf(" %d", tmp & 63);
        }
        // printf(" : %d\n", it.second);
        if(m >= 3)
            modInc(ans, mod - it.second);
    }
    printf("%d\n", ans);
}

int main() {
    int T = 1;
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
