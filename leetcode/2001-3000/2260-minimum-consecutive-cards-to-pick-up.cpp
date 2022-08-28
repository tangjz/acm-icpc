class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        int n = cards.size(), ans = n + 1;
        unordered_map<int, int> las;
        for(int i = 0; i < n; ++i) {
            int x = cards[i];
            auto it = las.find(x);
            if(it != las.end()) {
                ans = min(ans, i - (it -> second) + 1);
            }
            las[x] = i;
        }
        return ans <= n ? ans : -1;
    }
};
