class Solution {
public:
    int twoSumLessThanK(vector<int>& nums, int k) {
        int ans = -1, n = nums.size();
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j) {
                int tmp = nums[i] + nums[j];
                if(tmp < k)
                    ans = max(ans, tmp);
            }
        return ans;
    }
};
