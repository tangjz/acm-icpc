class Solution {
    bool isAlphanumeric(char ch) {
        return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9');
    }
    char toLower(char ch) {
        return ch >= 'A' && ch <= 'Z' ? (ch - 'A' + 'a') : ch;
    }
public:
    bool isPalindrome(string s) {
        for(int i = 0, j = (int)s.size() - 1; i <= j; ++i, --j) {
            for( ; i <= j && !isAlphanumeric(s[i]); ++i);
            for( ; i <= j && !isAlphanumeric(s[j]); --j);
            if(i <= j && toLower(s[i]) != toLower(s[j]))
                return 0;
        }
        return 1;
    }
};
