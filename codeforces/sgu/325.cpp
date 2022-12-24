#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1, maxc = 26;

char buf[maxn];
int n, bits[maxn], ctr[maxc + 1], rem[maxc + 1];
vector<int> cand[maxc + 1];

int main() {
    scanf("%s", buf);
    for(n = 0; buf[n]; ++n) {
        ++ctr[(int)(buf[n] - 'A')];
    }
    int odd = 0;
    for(int i = 0; i < maxc; ++i) {
        odd += ctr[i] & 1;
        rem[i] = ctr[i] >> 1;
        cand[i].reserve(rem[i]);
    }
    if((n & 1) != odd) {
        puts("-1");
        return 0;
    }
    long long ans = 0;
    for(int i = 0, j = 0, c = n & 1; i < n; ++i) {
        int o = buf[i] - 'A', pos;
        if(rem[o]) {
            --rem[o];
            cand[o].push_back(n - 1 - j);
            pos = j++;
        } else if(c && (ctr[o] & 1)) {
            --c;
            pos = n >> 1;
        } else {
            pos = cand[o].back();
            cand[o].pop_back();
        }
        for(int x = pos + 1; x < n; x += x & -x)
            ans += bits[x];
        for(int x = pos; x > 0; x -= x & -x)
            ++bits[x];
    }
    printf("%lld\n", ans);
    return 0;
}
