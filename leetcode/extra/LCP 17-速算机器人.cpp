class Solution {
public:
    int calculate(string s) {
        int x = 1, y = 0;
        for(char ch: s)
            (ch == 'A' ? x : y) += x + y;
        return x + y;
    }
};
