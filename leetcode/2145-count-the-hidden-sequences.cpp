class Solution {
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        typedef long long LL;
        LL L = 0, R = 0, cur = 0;
        for(int x: differences) {
            cur += x;
            if(cur < L) {
                L = cur;
            } else if(cur > R) {
                R = cur;
            }
        }
        LL p = R - L, q = upper - lower;
        return p <= q ? q - p + 1 : 0;
    }
};
