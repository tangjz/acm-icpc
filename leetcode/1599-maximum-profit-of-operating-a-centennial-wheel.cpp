class Solution {
public:
    int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost) {
        const int maxd = 4;
        int n = (int)customers.size(), ans = -1, best = 0, cur = 0, rem = 0;
        for(int i = 0; i < n || rem > 0; ++i) {
            if(i < n)
                rem += customers[i];
            int tmp = min(rem, maxd);
            rem -= tmp;
            cur += tmp * boardingCost - runningCost;
            if(best < cur) {
                best = cur;
                ans = i + 1;
            }
        }
        return ans;
    }
};
