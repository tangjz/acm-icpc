class Solution {
public:
    double getProbability(vector<int>& a) {
        int n = (int)a.size(), sum = 0;
        for(int x : a)
            sum += x;
        vector<vector<double> > c(sum + 1, vector<double>(sum + 1, 0)), f(n + n + 1, vector<double>(sum + 1, 0));
        for(int i = 0; i <= sum; ++i) {
            c[i][0] = c[i][i] = 1;
            for(int j = 1; j < i; ++j)
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
        f[n][0] = 1;
        for(int i = 0, pre = 0, cur; i < n; ++i) {
            int upp = a[i];
            cur = pre + upp;
            vector<vector<double> > g(n + n + 1, vector<double>(sum + 1, 0));
            for(int j = -n; j <= n; ++j)
                for(int k = 0; k <= pre; ++k) {
                    if(f[n + j][k] <= 0)
                        continue;
                    for(int dt = 0; dt <= upp; ++dt) {
                        int u = j + (dt > 0) - (dt < upp);
                        int v = k + dt;
                        g[n + u][v] += f[n + j][k] * c[v][k] * c[cur - v][pre - k];
                    }
                }
            pre = cur;
            f = move(g);
        }
        sum >>= 1;
        double num = f[n][sum], den = 0;
        for(int i = -n; i <= n; ++i)
            den += f[n + i][sum];
        return num / den;
    }
};
