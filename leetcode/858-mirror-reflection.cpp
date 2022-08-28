class Solution {
public:
    int mirrorReflection(int p, int q) {
        int com = gcd(p, q);
        int x = (p / com) & 1, y = (q / com) & 1;
        return y ? 2 - x : -1 + x;
    }
};
