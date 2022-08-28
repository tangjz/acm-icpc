class Solution {
public:
    int getSum(int a, int b) {
        while(b != 0) {
            int t = a ^ b;
            b = (unsigned)(a & b) << 1;
            a = t;
        }
        return a;
    }
};
