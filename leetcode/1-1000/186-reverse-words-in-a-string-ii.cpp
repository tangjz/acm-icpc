class Solution {
public:
    void reverseWords(vector<char>& s) {
        int len = (int)s.size();
        for(int i = 0; i < len; ++i) {
            if(s[i] == ' ')
                continue;
            int pre = i;
            for( ; i < len && s[i] != ' '; ++i);
            reverse(s.begin() + pre, s.begin() + i);
        }
        reverse(s.begin(), s.end());
    }
};
