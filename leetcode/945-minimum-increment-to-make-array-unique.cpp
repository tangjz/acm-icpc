class Solution {
public:
    int minIncrementForUnique(vector<int>& nums) {
        int las = -1, ans = 0;
        sort(nums.begin(), nums.end());
        for(int x: nums) {
            las = max(las + 1, x);
            ans += las - x;
        }
        return ans;
    }
};
