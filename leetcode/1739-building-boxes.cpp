class Solution {
public:
    int minimumBoxes(int n) {
        int L = 1, R = n;
        while(L < R) {
            int M = (L + R) >> 1;
            long long cnt = M;
            int rem = M, full = 0;
            while(rem >= full + 1) {
                rem -= ++full;
            }
            int cur = M;
            for(int i = full - 1; i >= 1; --i) {
                if(rem > 0) {
                    --rem;
                    --cur;
                }
                cur -= i + 1;
                cnt += cur;
            }
            if(cnt < n) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        return L;
    }
};
