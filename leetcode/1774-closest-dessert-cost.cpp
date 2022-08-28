class Solution {
public:
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        int upp = *max_element(toppingCosts.begin(), toppingCosts.end()) + target + 1;
        vector<bool> f(upp);
        f[0] = 1;
        for(int x: toppingCosts) {
            vector<bool> g(f.begin(), f.end());
            for(int i = 0; i < upp; ++i)
                if(i >= x && !g[i]) {
                    if(f[i - x])
                        g[i] = 1;
                    else if(i >= x + x && f[i - x - x])
                        g[i] = 1;
                }
            f = move(g);
        }
        pair<int, int> ans = {INT_MAX, 0};
        for(int x: baseCosts) {
            int pos = min(max(target - x, 0), upp);
            for(int i = 0; i < upp; ++i) {
                if(pos - i >= 0 && f[pos - i]) {
                    int y = x + pos - i;
                    ans = min(ans, {abs(target - y), y});
                    break;
                }
                if(pos + i < upp && f[pos + i]) {
                    int y = x + pos + i;
                    ans = min(ans, {abs(target - y), y});
                    break;
                }
            }
        }
        return ans.second;
    }
};
