class Solution {
public:
    int add(int a, int b) {
        while(b != 0) {
            unsigned t = a & b;
            a ^= b;
            b = t << 1;
        }
        return a;
    }
};
