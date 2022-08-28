class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int, int> > dis(n, {INT_MAX, -1});
        for(int i = 0; i < n; ++i) {
            if(dis[i].second != -1)
                continue;
            for(int u = i, d = 0; u != -1; u = (u + nums[u] % n + n) % n, ++d) {
                if(dis[u].first != INT_MAX) {
                    if(dis[u].second == i && d - dis[u].first > 1) {
                        int msk = 0;
                        for(int rem = d - dis[u].first; rem > 0; --rem, u = (u + nums[u] % n + n) % n)
                            msk |= 1 << (nums[u] > 0);
                        if(msk != 3)
                            return 1;
                    }
                    break;
                }
                dis[u] = {d, i};
            }
        }
        return 0;
    }
};
