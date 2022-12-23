class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        typedef long long LL;
        int n = nums.size();
        unordered_map<int, int> ctr;
        LL cur = 0, ans = 0;
        for(int i = 0; i < n; ++i) {
            ++ctr[nums[i]];
            cur += nums[i];
            if(i >= k - 1) {
                if(ctr.size() == k)
                    ans = max(ans, cur);
                int j = i - k + 1;
                if(!(--ctr[nums[j]]))
                    ctr.erase(nums[j]);
                cur -= nums[j];
            }
        }
        return ans;
    }
};
