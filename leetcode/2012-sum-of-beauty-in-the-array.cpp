class Solution {
public:
    int sumOfBeauties(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 1);
        for(int i = 1, o = INT_MIN; i < n; ++i) {
            o = max(o, nums[i - 1]);
            res[i] &= o < nums[i];
        }
        for(int i = n - 2, o = INT_MAX; i >= 0; --i) {
            o = min(o, nums[i + 1]);
            res[i] &= nums[i] < o;
        }
        int ans = 0;
        for(int i = 1; i + 1 < n; ++i) {
            ans += res[i];
            ans += nums[i - 1] < nums[i] && nums[i] < nums[i + 1];
        }
        return ans;
    }
};
