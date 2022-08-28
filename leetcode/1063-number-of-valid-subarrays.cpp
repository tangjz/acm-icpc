class Solution {
public:
    int validSubarrays(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> pR(n);
        for(int i = n - 1; i >= 0; --i) {
            for(pR[i] = i + 1; pR[i] < n && nums[i] <= nums[pR[i]]; pR[i] = pR[pR[i]]);
            ans += pR[i] - i;
        }
        return ans;
    }
};
