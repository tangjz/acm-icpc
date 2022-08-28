class Solution {
public:
    vector<int> numMovesStones(int a, int b, int c) {
        int n = 3;
        vector<int> stones = {a, b, c};
        sort(stones.begin(), stones.end());
        int upp = stones[n - 1] - stones[0] - (n - 1);
        int low = upp;
        if(upp > 0) {
            for(int i = 0, j = 0; i < n; ++i) {
                for( ; j < n && stones[j] - stones[i] <= n - 1; ++j);
                low = min(low, n - (j - i));
            }
        }
        return {low, upp};
    }
};
