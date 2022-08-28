#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &m, &n);
    vector<int> req(n);
    for(int i = 0; i < n; ++i)
        scanf("%d", &req[i]);
    while(!req.empty() && !req.back())
        req.pop_back();
    n = req.size();
    int L = n, R = (int)1e9;
    while(L < R) {
        int M = (L + R) >> 1;
        bool bad = 0;
        vector<int> rem(req.begin(), req.end());
        for(int i = 0; i < m && !rem.empty(); ++i) {
            int cnt = M - rem.size();
            while(cnt > 0 && !rem.empty())
                if(cnt < rem.back()) {
                    rem.back() -= cnt;
                    break;
                } else {
                    cnt -= rem.back();
                    rem.pop_back();
                }
            bad |= cnt < 0;
        }
        if(rem.empty() && !bad) {
            R = M;
        } else {
            L = M + 1;
        }
    }
    printf("%d\n", L);
    return 0;
}
