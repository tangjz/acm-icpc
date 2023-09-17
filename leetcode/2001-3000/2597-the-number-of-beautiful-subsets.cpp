class Solution {
public:
    int beautifulSubsets(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0;
        sort(nums.begin(), nums.end());
        for(int i = 1; i < (1 << n); ++i) {
            static int st = 0, vis[1001] = {};
            if(!(++st)) {
                memset(vis, 0, sizeof vis);
                ++st;
            }
            bool bad = 0;
            for(int j = 0; j < n; ++j) {
                if(!((i >> j) & 1))
                    continue;
                int v = nums[j];
                if(v >= k && vis[v - k] == st) {
                    bad = 1;
                    break;
                }
                vis[v] = st;
            }
            ans += !bad;
        }
        return ans;
    }
};
