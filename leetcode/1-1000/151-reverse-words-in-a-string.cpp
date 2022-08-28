class Solution {
public:
    string reverseWords(string s) {
        int len = (int)s.length(), cnt = 0;
        for(int i = 0; i < len; ++i) {
            if(s[i] == ' ')
                continue;
            int pre = cnt;
            for( ; i < len && s[i] != ' '; ++i)
                s[cnt++] = s[i];
            reverse(s.begin() + pre, s.begin() + cnt);
            if(i < len)
                s[cnt++] = ' ';
        }
        if(cnt > 0 && s[cnt - 1] == ' ')
            --cnt;
        s.resize(cnt);
        reverse(s.begin(), s.end());
        return s;
    }
};
