class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& numsDivide) {
        int m = 0;
        for(int x: numsDivide)
            m = gcd(m, x);
        int n = nums.size();
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n; ++i)
            if(m % nums[i] == 0)
                return i;
        return -1;
    }
};
