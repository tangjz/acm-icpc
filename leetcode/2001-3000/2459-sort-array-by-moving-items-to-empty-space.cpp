class Solution {
public:
    int sortArray(vector<int>& nums) {
        int n = nums.size(), ans = n + n;
        vector<bool> vis(n);
        for(int i = 0, sp = 0; i < 2; ++i) {
            int cur = n;
            vis.assign(n, false);
            for(int j = 0; j < n; ++j) {
                if(vis[j])
                    continue;
                int c = 0;
                bool hasSP = 0;
                for(int k = j; !vis[k]; hasSP |= k == sp, vis[k] = 1, ++c, k = nums[k]);
                if(c == 1 || hasSP) {
                    --cur;
                } else {
                    ++cur;
                }
            }
            ans = min(ans, cur);
            if(!i) {
                sp = n - 1;
                for(int &x: nums)
                    (--x) < 0 && (x = n - 1);
            }
        }
        return ans;
    }
};
