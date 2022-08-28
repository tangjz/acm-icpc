class Solution {
public:
    long long ringGame(vector<long long>& challenge) {
        typedef long long LL;
        int n = challenge.size(), m = n * 3, mx = 0;
        vector<LL> seq(m);
        vector<pair<LL, int> > pL(m), pR(m);
        for(int i = 0; i < m; ++i) {
            pL[i].first = seq[i] = i < n ? challenge[i] : seq[i - n];
            for(int &j = pL[i].second = i - 1; j >= 0 && seq[j] <= pL[i].first; j = pL[j].second)
                pL[i].first |= pL[j].first;
            for( ; (1LL << mx) <= seq[i]; ++mx);
        }
        for(int i = m - 1; i >= 0; --i) {
            pR[i].first = seq[i];
            for(int &j = pR[i].second = i + 1; j < m && seq[j] <= pR[i].first; j = pR[j].second)
                pR[i].first |= pR[j].first;
        }
        auto check = [&](LL sta) {
            for(int i = n; i < n + n; ++i) {
                if(seq[i] > sta)
                    continue;
                int L = i, R = i;
                LL cur = sta;
                while(R - L - 1 < n) {
                    if(cur >= seq[L]) {
                        cur |= pL[L].first;
                        L = pL[L].second;
                    } else if(cur >= seq[R]) {
                        cur |= pR[R].first;
                        R = pR[R].second;
                    } else {
                        break;
                    }
                }
                if(R - L - 1 >= n)
                    return 1;
            }
            return 0;
        };
        LL ans = 1LL << (mx - 1);
        for(int i = mx - 2; i >= 0; --i)
            if(!check(ans | ((1LL << i) - 1)))
                ans |= 1LL << i;
        return ans;
    }
};
