class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k) {
        int n = (int)nums.size(), las = -n;
        for(int i = 0; i < n; ++i)
            if(nums[i] == 1) {
                if(i - las - 1 < k)
                    return 0;
                las = i;
            }
        return 1;
    }
};
