class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        int x = 0, y = 0;
        for(char ch: moves) {
            x += ch == 'R' ? 1 : -1;
            y += ch == 'L' ? -1 : 1;
        }
        return max(abs(x), abs(y));
    }
};
