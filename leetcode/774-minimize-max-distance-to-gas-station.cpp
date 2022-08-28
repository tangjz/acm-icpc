class Solution {
public:
    double minmaxGasDist(vector<int>& stations, int k) {
        int n = stations.size();
        double L = 0, R = stations.back() - stations.front();
        while(R - L >= 1e-6) {
            double M = (L + R) / 2;
            int cnt = 0;
            for(int i = 1; i < n; ++i)
                cnt += ceil((stations[i] - stations[i - 1]) / M) - 1;
            if(cnt > k) {
                L = M;
            } else {
                R = M;
            }
        }
        return R;
    }
};
