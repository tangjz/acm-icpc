class Solution {
public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        typedef long long LL;
        map<int, LL> ctr[2];
        for(auto &it : orders) {
            int p = it[0], c = it[1], t = it[2];
            if(t == 0) {
                while(!ctr[!t].empty() && c > 0 && ctr[!t].begin() -> first <= p) {
                    auto jt = ctr[!t].begin();
                    LL d = min((LL)c, jt -> second);
                    c -= d;
                    if(d == jt -> second) {
                        ctr[!t].erase(jt);
                    } else {
                        jt -> second -= d;
                    }
                }
            } else {
                while(!ctr[!t].empty() && c > 0 && ctr[!t].rbegin() -> first >= p) {
                    auto jt = ctr[!t].rbegin();
                    LL d = min((LL)c, jt -> second);
                    c -= d;
                    if(d == jt -> second) {
                        ctr[!t].erase(--ctr[!t].end());
                    } else {
                        jt -> second -= d;
                    }
                }
            }
            if(c > 0)
                ctr[t][p] += c;
        }
        const int mod = (int)1e9 + 7;
        int ans = 0;
        for(int i = 0; i < 2; ++i)
            for(auto &it : ctr[i])
                ans = (ans + it.second) % mod;
        return ans;
    }
};
