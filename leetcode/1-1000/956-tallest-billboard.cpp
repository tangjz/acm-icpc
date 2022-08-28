class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        int sum = 0;
        vector<int> f = {0};
        for(int x: rods) {
            vector<int> g(sum + x + 1, -1);
            for(int i = 0; i <= sum; ++i) {
                if(f[i] == -1)
                    continue;
                g[i] = max(g[i], f[i]);
                g[i + x] = max(g[i + x], f[i]);
                if(i < x) {
                    g[x - i] = max(g[x - i], f[i] + i);
                } else {
                    g[i - x] = max(g[i - x], f[i] + x);
                }
            }
            f = move(g);
            sum += x;
        }
        return f[0];
    }
};
