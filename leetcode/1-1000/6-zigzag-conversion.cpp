class Solution {
public:
    string convert(string s, int numRows) {
        int n = s.size(), m = max(numRows - 2, 0);
        string t = "";
        for(int i = 0; i < numRows; ++i)
            for(int j = 0; j + i < n; j += numRows + m) {
                t.push_back(s[j + i]);
                if(i > 0 && i + 1 < numRows && j + numRows + m - i < n)
                    t.push_back(s[j + numRows + m - i]);
            }
        return move(t);
    }
};
