class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        vector<pair<int, int> > ctr;
        for(int x: nums)
            if(ctr.empty() || ctr.back().first != x) {
                ctr.push_back({x, 1});
            } else {
                ++ctr.back().second;
            }
        int ans = 0, n = ctr.size();
        for(int i = 0; i < n; ++i)
            if(ctr[i].first) {
                ans = max(ans, ctr[i].second);
            } else {
                int lft = i > 0 ? ctr[i - 1].second : 0;
                int rht = i + 1 < n ? ctr[i + 1].second : 0;
                ans = max(ans, ctr[i].second == 1 ? lft + 1 + rht : max(lft, rht) + 1);
            }
        return ans;
    }
};
