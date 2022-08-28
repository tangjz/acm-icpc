class Solution {
public:
    int subtractProductAndSum(int n) {
        int prd = 1, sum = 0;
        for( ; n > 0; n /= 10) {
            int x = n % 10;
            prd *= x;
            sum += x;
        }
        return prd - sum;
    }
};
