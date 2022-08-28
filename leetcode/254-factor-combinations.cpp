class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        vector<int> cur;
        vector<vector<int> > ret;
        function<void(int, int)> dfs = [&](int x, int d) {
            if(x < d)
                return;
            for(int i = d; i * i <= x; ++i) {
                if(x % i > 0)
                    continue;
                cur.push_back(i);
                dfs(x / i, i);
                cur.pop_back();
            }
            cur.push_back(x);
            if(cur.size() > 1)
                ret.push_back(cur);
            cur.pop_back();
        };
        dfs(n, 2);
        return ret;
    }
};
