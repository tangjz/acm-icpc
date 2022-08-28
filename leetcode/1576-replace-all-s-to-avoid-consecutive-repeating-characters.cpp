class Solution {
public:
    string modifyString(string s) {
        int n = (int)s.size();
        for(int i = 0; i < n; ++i)
            if(s[i] == '?') {
                for(char ch = 'a'; ch <= 'z'; ++ch)
                    if((i == 0 || ch != s[i - 1]) && (i == n - 1 || ch != s[i + 1])) {
                        s[i] = ch;
                        break;
                    }
            }
        return s;
    }
};
