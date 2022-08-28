class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0, las = prices.front() + 1;
        for(int x : prices) {
            ans += max(x - las, 0);
            las = x;
        }
        return ans;
    }
};
