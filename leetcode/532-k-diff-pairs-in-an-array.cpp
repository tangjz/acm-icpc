class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        if(!k) {
            int n = (int)nums.size(), ans = 0;
            for(int i = 0; i + 1 < n; ++i)
                if(!i || nums[i - 1] != nums[i])
                    ans += nums[i] == nums[i + 1];
            return ans;
        }
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        int n = (int)nums.size(), ans = 0;
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < i && nums[i] - nums[j] > k; ++j);
            ans += nums[i] - nums[j] == k;
        }
        return ans;
    }
};
