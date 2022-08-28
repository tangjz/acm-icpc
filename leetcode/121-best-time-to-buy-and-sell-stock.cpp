class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int best = 0, low = INT_MAX;
        for(int x : prices) {
            low = min(low, x);
            best = max(best, x - low);
        }
        return best;
    }
};
