class Solution {
public:
    string removeStars(string s) {
        int tot = 0;
        for(char ch: s)
            if(ch == '*') {
                --tot;
            } else {
                s[tot++] = ch;
            }
        s.resize(tot);
        return s;
    }
};
