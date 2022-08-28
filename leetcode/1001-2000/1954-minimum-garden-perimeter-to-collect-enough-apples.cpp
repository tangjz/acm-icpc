class Solution {
public:
    long long minimumPerimeter(long long neededApples) {
        typedef long long LL;
        LL L = 0, R = (LL)1e5;
        while(L < R) {
            LL M = (L + R) >> 1;
            LL cnt = 2 * (M << 1 | 1) * M * (M + 1);
            if(cnt < neededApples) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        return L * 8;
    }
};
