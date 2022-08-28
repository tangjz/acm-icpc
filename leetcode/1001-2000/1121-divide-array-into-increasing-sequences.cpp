class Solution {
public:
    bool canDivideIntoSubsequences(vector<int>& nums, int k) {
        int n = nums.size(), m = n / k;
        for(int i = 0, j = 0; i < n; i = j) {
            for( ; j < n && nums[i] == nums[j]; ++j);
            if(j - i > m)
                return 0;
        }
        return 1;
    }
};
