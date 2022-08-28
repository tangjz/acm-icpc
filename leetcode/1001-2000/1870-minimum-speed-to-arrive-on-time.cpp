class Solution {
public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int n = (int)dist.size();
        if(hour < n - 1)
            return -1;
        int L = 1, R = (int)1e7 + 1;
        while(L < R) {
            int M = (L + R) >> 1;
            double ctr = 0;
            for(int i = 0; i < n; ++i) {
                double adt = (double)dist[i] / M;
                if(i + 1 < n)
                    adt = ceil(adt);
                ctr += adt;
            }
            if(ctr > hour) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        return L < (int)1e7 + 1 ? L : -1;
    }
};
