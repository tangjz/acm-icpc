#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int mod = (int)1e9 + 7;

int main() {
    int low = INT_MAX, upp = INT_MIN;
    vector<vector<int> > que;
    for(int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2) == 4; ) {
        que.push_back({x1, y1, x2, y2});
        low = min(low, *min_element(que.back().begin(), que.back().end()));
        upp = max(upp, *max_element(que.back().begin(), que.back().end()));
    }
    if(que.empty())
        return 0;
    int mx = (upp - low) * 2 + 3;
    vector<int> fct(mx), ifct(mx);
    ifct[1] = 1;
    for(int i = 2; i < mx; ++i)
        ifct[i] = mod - (int)(mod / i * (LL)ifct[mod % i] % mod);
    fct[0] = ifct[0] = 1;
    for(int i = 1; i < mx; ++i) {
        fct[i] = (LL)fct[i - 1] * i % mod;
        ifct[i] = (LL)ifct[i - 1] * ifct[i] % mod;
    }
    auto calc = [&](int x, int y) {
        return (LL)fct[x + y] * ifct[x] % mod * ifct[y] % mod;
    };
    for(auto &vec: que) {
        pair<int, int> u = {vec[0], vec[1]}, v = {vec[2], vec[3]};
        if(u.first > u.second || v.first > v.second) {
            puts("0");
            continue;
        }
        if(u > v)
            swap(u, v);
        int ans = calc(abs(u.first - v.first), abs(u.second - v.second));
        u = {u.second + 1, u.first - 1};
        if(u.first <= v.first && u.second <= v.second)
            (ans -= calc(v.first - u.first, v.second - u.second)) < 0 && (ans += mod);
        printf("%d\n", ans);
    }
    return 0;
}
