class Solution {
public:
    vector<int> numsSameConsecDiff(int n, int k) {
        const int maxd = 10;
        vector<int> f;
        for(int i = 1; i < maxd; ++i)
            f.push_back(i);
        for(int i = 1; i < n; ++i) {
            vector<int> g, h;
            for(int x: f) {
                int d = x % 10;
                x *= 10;
                if(d - k >= 0)
                    g.push_back(x + d - k);
                if(d + k < maxd)
                    h.push_back(x + d + k);
            }
            int x = g.size();
            g.insert(g.end(), h.begin(), h.end());
            inplace_merge(g.begin(), g.begin() + x, g.end());
            g.erase(unique(g.begin(), g.end()), g.end());
            f = move(g);
        }
        return f;
    }
};
