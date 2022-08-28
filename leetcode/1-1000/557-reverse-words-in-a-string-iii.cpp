class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        for(int i = 0, j; i < n; ) {
            if(s[i] == ' ') {
                ++i;
                continue;
            }
            for(j = i; i < n && s[i] != ' '; ++i);
            reverse(s.begin() + j, s.begin() + i);
        }
        return move(s);
    }
};
