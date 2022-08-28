class Solution {
public:
    int minTime(vector<int>& time, int m) {
        int n = time.size(), L = 0, R = accumulate(time.begin(), time.end(), 0);
        while(L < R) {
            int M = (L + R) >> 1;
            int ctr = 0;
            for(int i = 0, j; i < n; ) {
                int sum = 0, upp = 0;
                for(j = i; i < n; ++i) {
                    sum += time[i];
                    upp = max(upp, time[i]);
                    if(sum - upp > M)
                        break;
                }
                if(j == i) {
                    ctr = m + 1;
                    break;
                }
                ++ctr;
            }
            if(ctr <= m) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
