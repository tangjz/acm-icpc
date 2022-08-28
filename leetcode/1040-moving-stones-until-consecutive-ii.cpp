class Solution {
public:
    vector<int> numMovesStonesII(vector<int>& stones) {
        int n = stones.size();
        sort(stones.begin(), stones.end());
        int upp = stones[n - 1] - stones[0] - (n - 2) - min(stones[1] - stones[0], stones[n - 1] - stones[n - 2]);
        int low = upp;
        if(upp > 0) {
            for(int i = 0, j = 0; i < n; ++i) {
                for( ; j < n && stones[j] - stones[i] <= n - 1; ++j);
                if(!i && stones[n - 2] - stones[0] == n - 2) {
                    low = min(low, 2);
                    continue;
                }
                if(i == 1 && stones[n - 1] - stones[1] == n - 2) {
                    low = min(low, 2);
                    continue;
                }
                if(j == n && stones[n - 1] - stones[i] < n - 1)
                    break;
                low = min(low, n - (j - i));
            }
        }
        return {low, upp};
    }
};
