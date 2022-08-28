class Solution {
public:
    int maxLength(vector<int>& ribbons, int k) {
        int L = 0, R = (int)1e5 + 1;
        while(L < R) {
            int M = (L + R + 1) >> 1;
            int cnt = 0;
            for(int x: ribbons)
                cnt += x / M;
            if(cnt < k) {
                R = M - 1;
            } else {
                L = M;
            }
        }
        return L;
    }
};
