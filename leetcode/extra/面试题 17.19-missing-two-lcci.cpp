class Solution {
public:
    vector<int> missingTwo(vector<int>& nums) {
        int n = nums.size(), sum = (n + 1) ^ (n + 2);
        for(int i = 0; i < n; ++i)
            sum ^= nums[i] ^ (i + 1);
        sum = sum & -sum;
        int lft = 0, rht = 0;
        ((n + 1) & sum ? lft : rht) ^= n + 1;
        ((n + 2) & sum ? lft : rht) ^= n + 2;
        for(int i = 0; i < n; ++i) {
            (nums[i] & sum ? lft : rht) ^= nums[i];
            ((i + 1) & sum ? lft : rht) ^= i + 1;
        }
        return {lft, rht};
    }
};
