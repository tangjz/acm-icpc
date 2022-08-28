class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        typedef long long LL;
        int n = speed.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return position[u] < position[v];
        });
        stack<pair<int, int> > stk;
        for(int i = 0; i < n; ++i) {
            pair<int, int> cur = {position[ord[i]], speed[ord[i]]};
            while(!stk.empty()) {
                pair<int, int> pre = stk.top();
                if((LL)pre.second * (cur.first - pre.first) > (LL)(target - pre.first) * (pre.second - cur.second))
                    break;
                stk.pop();
            }
            stk.push(cur);
        }
        return stk.size();
    }
};
