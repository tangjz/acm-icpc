class Solution {
public:
    int splitArray(vector<int>& nums) {
        static const int maxv = (int)1e6 + 1, maxe = 9;
        static int fct[maxv][maxe] = {};
        if(!fct[2][0]) {
            for(int i = 2; i < maxv; ++i)
                if(!fct[i][0])
                    for(int j = i; j < maxv; j += i)
                        fct[j][++fct[j][0]] = i;
        }
        static const int maxn = (int)1e5 + 1;
        static int st = 0;
        static pair<int, int> f[maxn] = {}, g[maxv] = {};
        if(!(++st)) {
            memset(f, 0, sizeof f);
            memset(g, 0, sizeof g);
            ++st;
        }
        int n = nums.size();
        f[0] = {0, st};
        for(int i = 0; i < n; ++i) {
            f[i + 1] = {INT_MAX, st};
            int u = nums[i], v;
            for(int j = 1; j <= fct[u][0]; ++j) {
                v = fct[u][j];
                if(g[v].second != st) {
                    g[v] = f[i];
                } else {
                    g[v].first = min(g[v].first, f[i].first);
                }
                f[i + 1].first = min(f[i + 1].first, g[v].first + 1);
            }
        }
        return f[n].first;
    }
};
