class Solution {
public:
    int integerBreak(int n) {
        if(n < 2 + 2) {
            return n - 1;
        }
        int prd = 1;
        while(n > 4) {
            prd *= 3;
            n -= 3;
        }
        prd *= n;
        return prd;
    }
};
