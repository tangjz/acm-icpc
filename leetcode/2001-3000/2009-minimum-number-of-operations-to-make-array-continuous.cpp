class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int ans = n;
        unordered_map<int, int> ctr;
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < n && nums[j] < nums[i] + n; ++j) {
                auto it = ctr.find(nums[j]);
                ctr[nums[j]] += 1;
            }
            ans = min(ans, n - (int)ctr.size());
            if(ctr[nums[i]] == 1) {
                ctr.erase(nums[i]);
            } else {
                ctr[nums[i]] -= 1;
            }
        }
        return ans;
    }
};
