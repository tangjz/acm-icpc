class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        const int maxd = 3, cost[maxd] = {5, 10, 20};
        int ctr[maxd] = {};
        for(int x: bills) {
            int pos = 0;
            for( ; cost[pos] < x; ++pos);
            ++ctr[pos];
            x -= cost[0];
            for(--pos; pos >= 0; --pos) {
                int tmp = min(ctr[pos], x / cost[pos]);
                ctr[pos] -= tmp;
                x -= tmp * cost[pos];
            }
            if(x > 0)
                return 0;
        }
        return 1;
    }
};
