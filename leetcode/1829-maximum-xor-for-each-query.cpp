class Solution {
public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        int sum = (1 << maximumBit) - 1;
        for(int x: nums)
            sum ^= x;
        vector<int> ans;
        reverse(nums.begin(), nums.end());
        for(int x: nums) {
            ans.push_back(sum);
            sum ^= x;
        }
        return ans;
    }
};
