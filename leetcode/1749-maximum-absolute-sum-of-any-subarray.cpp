class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int sum = 0, ans = 0, low = 0, upp = 0;
        for(int x : nums) {
            low = min(low, sum);
            upp = max(upp, sum);
            sum += x;
            ans = max(ans, max(upp - sum, sum - low));
        }
        return ans;
    }
};
