class Solution {
public:
    long long waysToBuyPensPencils(int total, int cost1, int cost2) {
        long long ans = 0;
        for(int i = 0; total >= 0; ++i, total -= cost1)
            ans += total / cost2 + 1;
        return ans;
    }
};
