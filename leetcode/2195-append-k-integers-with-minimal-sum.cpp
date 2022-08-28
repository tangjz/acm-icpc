class Solution {
public:
    long long minimalKSum(vector<int>& nums, int k) {
        int las = 0;
        long long ans = 0;
        sort(nums.begin(), nums.end());
        for(int x: nums) {
            if(x == las)
                continue;
            if(x <= k) {
                ans -= x;
                ++k;
            } else {
                break;
            }
            las = x;
        }
        ans += k * (k + 1LL) / 2;
        return ans;
    }
};
