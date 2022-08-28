class Solution {
public:
    double myPow(double x, int n) {
        if(!n)
            return 1;
        if(fabs(x) < 1e-9)
            return 0;
        return (n & 1 && x < 0 ? -1 : 1) * exp(log(fabs(x)) * n);
    }
};
