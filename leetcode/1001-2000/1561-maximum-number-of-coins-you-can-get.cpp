class Solution {
public:
    int maxCoins(vector<int>& piles) {
        int n = (int)piles.size() / 3;
        sort(piles.begin(), piles.end(), greater<int>());
        int ans = 0;
        for(int i = 0; i < n; ++i)
            ans += piles[i << 1 | 1];
        return ans;
    }
};
