class Solution {
public:
    long long maximumSumScore(vector<int>& nums) {
        long long ans = LLONG_MIN, lft = 0, rht = 0;
        for(int x: nums)
            rht += x;
        for(int x: nums) {
            lft += x;
            ans = max(ans, max(lft, rht));
            rht -= x;
        }
        return ans;
    }
};
