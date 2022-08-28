class Solution {
public:
    double probabilityOfHeads(vector<double>& prob, int target) {
        const double INF = 1e20;
        vector<double> f = {1};
        for(double x: prob) {
            if(x == 0)
                continue;
            if(x == 1) {
                --target;
                if(target < 0)
                    return 0;
                continue;
            }
            int n = f.size();
            f.push_back(f.back() * x);
            for(int i = n - 1; i > 0; --i)
                f[i] = f[i] * (1 - x) + f[i - 1] * x;
            f[0] = f[0] * (1 - x);
            if(f.size() > target + 1)
                f.resize(target + 1);
        }
        return f.back();
    }
};
