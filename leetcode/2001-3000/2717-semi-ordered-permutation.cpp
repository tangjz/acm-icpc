class Solution {
public:
    int semiOrderedPermutation(vector<int>& nums) {
        int n = nums.size(), pL = -1, pR = -1;
        for(int i = 0; i < n; ++i)
            if(nums[i] == 1) {
                pL = i;
            } else if(nums[i] == n) {
                pR = i;
            }
        return pL + n - 1 - pR - (pL > pR);
    }
};
