class Solution {
public:
    int countElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int low = nums.front(), upp = nums.back(), ans = 0;
        for(int x: nums)
            ans += x > low && x < upp;
        return ans;
    }
};
