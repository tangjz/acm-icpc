class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        for(int i = 0, j = n - 1; i < j; ++i) {
            for( ; i < j && nums[i] + nums[j] > target; --j);
            if(i < j && nums[i] + nums[j] == target)
                return {i + 1, j + 1};
        }
        return {};
    }
};
