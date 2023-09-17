class Solution {
public:
    int longestString(int x, int y, int z) {
        int t = min(x, y) + 1;
        x = min(x, t);
        y = min(y, t);
        return (x + y + z) * 2;
    }
};
