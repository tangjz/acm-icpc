class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        int ret = 1, prd = 1;
        for(int i = 0; i < 10 && i < n; ++i) {
            prd *= 10 - i - !i;
            ret += prd;
        }
        return ret;
    }
};
