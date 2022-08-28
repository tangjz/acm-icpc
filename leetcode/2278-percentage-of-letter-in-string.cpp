class Solution {
public:
    int percentageLetter(string s, char letter) {
        int n = s.size(), m = 0;
        for(char ch: s)
            m += ch == letter;
        return 100 * m / n;
    }
};
