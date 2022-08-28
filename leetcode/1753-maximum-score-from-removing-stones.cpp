class Solution {
public:
    int maximumScore(int a, int b, int c) {
        int sum = a + b + c, mx = max(a, max(b, c));
        return sum - mx < mx ? sum - mx : sum >> 1;
    }
};
