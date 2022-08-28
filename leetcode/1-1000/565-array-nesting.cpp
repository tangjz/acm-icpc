class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        for(int i = 0; i < n; ++i) {
            if(nums[i] < 0)
                continue;
            int cnt = 0;
            for(int j = i, k; nums[j] >= 0; ++cnt, k = j, j = nums[j], nums[k] = -1);
            ans = max(ans, cnt);
        }
        return ans;
    }
};
