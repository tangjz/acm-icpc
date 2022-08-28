class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size(), low = nums[0], upp = low;
        for(int x: nums)
            if(x < low) {
                low = x;
            } else if(x > upp) {
                upp = x;
            }
        int rng = upp - low;
        if(!rng || n == 2)
            return rng;
        int stp = max(rng / (n - 1), 1), m = rng / stp + 1;
        vector<pair<int, int> > seq(m, {INT_MAX, INT_MIN});
        for(int x: nums) {
            int y = (x - low) / stp;
            if(seq[y].first == INT_MAX) {
                seq[y] = {x, x};
            } else if(x < seq[y].first) {
                seq[y].first = x;
            } else if(x > seq[y].second) {
                seq[y].second = x;
            }
        }
        int ans = stp, las = INT_MIN;
        for(auto &it: seq) {
            if(it.first == INT_MAX)
                continue;
            if(las != INT_MIN)
                ans = max(ans, it.first - las);
            las = it.second;
        }
        return ans;
    }
};
