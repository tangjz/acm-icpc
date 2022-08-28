class Solution {
public:
    int convertInteger(int A, int B) {
        return __builtin_popcount(A ^ B);
    }
};
