class Solution {
public:
    int minimumSwaps(vector<int>& nums) {
        int n = nums.size(), pL = 0, pR = n - 1;
        for(int i = 1; i < n; ++i)
            if(nums[i] < nums[pL])
                pL = i;
        for(int i = n - 2; i >= 0; --i)
            if(nums[i] > nums[pR])
                pR = i;
        return pL + n - 1 - pR - (pL > pR);
    }
};
