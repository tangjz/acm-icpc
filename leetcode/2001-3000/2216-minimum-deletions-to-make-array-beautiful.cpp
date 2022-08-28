class Solution {
public:
    int minDeletion(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n + 1);
        int cnt = 0, pre = -2, ans = n;
        unordered_map<int, int> ctr;
        for(int i = 0, j = 0; i < n; ++i) { // nums: [j, i]
            cnt += !ctr.count(nums[i]);
            ++ctr[nums[i]];
            for( ; j <= i && cnt >= 2; ++j) {
                int v = --ctr[nums[j]];
                if(!v) {
                    --cnt;
                    ctr.erase(nums[j]);
                }
                pre = max(pre, dp[j]);
            }
            dp[i + 1] = pre + 2;
            // printf("%d: j %d dp %d\n", i, j, dp[i + 1]);
            ans = min(ans, n - dp[i + 1]);
        }
        return ans;
    }
};
