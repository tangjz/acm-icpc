class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size(), ans = n;
        vector<int> pre(n), suf(n);
        vector<int> que;
        for(int i = 0; i < n; ++i) {
            auto it = lower_bound(que.begin(), que.end(), nums[i]);
            pre[i] = it - que.begin() + 1;
            if(it == que.end()) {
                que.push_back(nums[i]);
            } else {
                *it = nums[i];
            }
        }
        que.clear();
        for(int i = n - 1; i >= 0; --i) {
            auto it = lower_bound(que.begin(), que.end(), nums[i]);
            suf[i] = it - que.begin() + 1;
            if(it == que.end()) {
                que.push_back(nums[i]);
            } else {
                *it = nums[i];
            }
            if(pre[i] >= 2 && suf[i] >= 2)
                ans = min(ans, n - pre[i] - suf[i] + 1);
        }
        return ans;
    }
};
