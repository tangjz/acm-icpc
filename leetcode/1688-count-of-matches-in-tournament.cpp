class Solution {
public:
    int numberOfMatches(int n) {
        return n > 1 ? (n >> 1) + numberOfMatches((n + 1) >> 1) : 0;
    }
};
