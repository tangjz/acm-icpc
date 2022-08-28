class Solution {
public:
    string largestGoodInteger(string s) {
        int n = s.size();
        char ch = '\0';
        for(int i = 0, j; i < n; i = j) {
            for(j = i; j < n && s[i] == s[j]; ++j);
            if(j - i >= 3)
                ch = max(ch, s[i]);
        }
        return ch ? string(3, ch) : "";
    }
};
