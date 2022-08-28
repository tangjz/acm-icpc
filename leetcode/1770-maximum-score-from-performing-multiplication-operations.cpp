class Solution {
public:
    int maximumScore(vector<int>& val, vector<int>& mul) {
        int n = (int)val.size(), m = (int)mul.size();
        vector<int> f(1, INT_MIN);
        f[0] = 0;
        for(int i = 0; i < m; ++i) {
            vector<int> g(i + 2, INT_MIN);
            auto upd_max = [&](int &x, int y) -> void {
                x < y && (x = y);
            };
            for(int j = 0; j <= i; ++j) {
                int L = j, R = n - 1 - (i - j);
                upd_max(g[j], f[j] + mul[i] * val[R]);
                upd_max(g[j + 1], f[j] + mul[i] * val[L]);
            }
            f = move(g);
        }
        return *max_element(f.begin(), f.end());
    }
};
