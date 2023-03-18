class Solution {
public:
    long long coloredCells(int n) {
        return n * (n - 1LL) * 2 + 1;
    }
};
