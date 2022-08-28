class Solution {
public:
    int minDays(vector<int>& a, int m, int k) {
        int n = (int)a.size();
        if(1LL * m * k > n)
            return -1;
        int L = 1, R = *max_element(a.begin(), a.end());
        while(L < R) {
            int M = (L + R) >> 1;
            int ctr = 0, las = -1, cur = 0;
            for(int x : a) {
                if(x > M) {
                    ctr += (cur - las - 1) / k;
                    las = cur;
                }
                ++cur;
            }
            ctr += (n - las - 1) / k;
            if(ctr >= m) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
