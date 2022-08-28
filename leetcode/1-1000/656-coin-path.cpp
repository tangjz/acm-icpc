class Solution {
public:
    vector<int> cheapestJump(vector<int>& coins, int maxJump) {
        const int INF = 0x3f3f3f3f;
        int n = coins.size();
        vector<pair<int, int> > f(n, {INF, -1});
        if(coins[n - 1] != -1)
            f[n - 1].first = coins[n - 1];
        for(int i = n - 2; i >= 0; --i) {
            if(coins[i] == -1)
                continue;
            for(int j = 1; j <= maxJump && i + j < n; ++j) {
                pair<int, int> tmp = {f[i + j].first, i + j};
                if(f[i] > tmp)
                    f[i] = tmp;
            }
            if(f[i].first == INF) {
                f[i].second = -1;
            } else {
                f[i].first += coins[i];
            }
        }
        if(f[0].first == INF)
            return {};
        vector<int> ret;
        for(int i = 0; i != -1; i = f[i].second)
            ret.push_back(i + 1);
        return ret;
    }
};
