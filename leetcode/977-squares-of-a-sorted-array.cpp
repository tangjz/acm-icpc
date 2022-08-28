class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size(), p = 0;
        for( ; p < n && nums[p] < 0; ++p);
        for(int &x: nums)
            x *= x;
        vector<int> ret;
        ret.reserve(n);
        for(int i = p - 1, j = p; i >= 0 || j < n; )
            if(j >= n || (i >= 0 && nums[i] < nums[j])) {
                ret.push_back(nums[i--]);
            } else {
                ret.push_back(nums[j++]);
            }
        return ret;
    }
};
