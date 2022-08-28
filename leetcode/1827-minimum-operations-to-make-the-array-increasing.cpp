class Solution {
public:
    int minOperations(vector<int>& nums) {
        int las = 0, ans = 0;
        for(int x: nums) {
            int cur = max(x, las + 1);
            ans += cur - x;
            las = cur;
        }
        return ans;
    }
};
