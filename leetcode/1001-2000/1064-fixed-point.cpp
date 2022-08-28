class Solution {
public:
    int fixedPoint(vector<int>& arr) {
        int L = 0, R = arr.size() - 1;
        while(L < R) {
            int M = (L + R) >> 1;
            int val = arr[M] - M;
            if(val < 0) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        return arr[L] == L ? L : -1;
    }
};
