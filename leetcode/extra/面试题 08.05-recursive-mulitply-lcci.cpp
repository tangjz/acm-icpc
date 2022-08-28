class Solution {
public:
    int multiply(int A, int B) {
        return !A || !B ? 0 : multiply(A >> 1, B << 1) + (A & 1 ? B : 0);
    }
};
