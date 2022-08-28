class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size(), pL = 0, pR = 0;
        if(n == 1)
            return 1;
        for(int i = 1; i < n; ++i) {
            if(nums[i] > nums[pR]) {
                pR = i;
            } else if(nums[i] < nums[pL]) {
                pL = i;
            }
        }
        if(pL > pR)
            swap(pL, pR);
        return min(pL + 1 + n - pR, min(pR + 1, n - pL));
    }
};
