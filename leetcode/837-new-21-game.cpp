class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        double sum = 0;
        vector<double> f(n + 1);
        f[n] = 1;
        for(int i = n - 1; i >= 0; --i) {
            sum += f[i + 1];
            if(i + maxPts + 1 <= n)
                sum -= f[i + maxPts + 1];
            if(i >= k) {            
                f[i] = 1;
            } else {
                f[i] = sum / maxPts;
            }
        }
        return f[0];
    }
};
