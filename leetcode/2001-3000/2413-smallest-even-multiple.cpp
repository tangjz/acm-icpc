class Solution {
public:
    int smallestEvenMultiple(int n) {
        (n & 1) && (n <<= 1);
        return n;
    }
};
