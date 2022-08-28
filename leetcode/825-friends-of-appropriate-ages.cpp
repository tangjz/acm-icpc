class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        int ans = 0;
        unordered_map<int, int> ctr;
        for(int x: ages)
            ++ctr[x];
        for(auto &it: ctr)
            for(auto &jt: ctr) {
                int u = it.first, v = jt.first;
                if(2 * v <= u + 14 || v > u || (v > 100 && u < 100))
                    continue;
                ans += it.second * (jt.second - (u == v));
            }
        return ans;
    }
};
