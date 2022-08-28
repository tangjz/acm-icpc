class Solution {
public:
    string removeDuplicateLetters(string s) {
        const int maxd = 26;
        int pos = 0;
        vector<int> las(maxd);
        vector<bool> vis(maxd);
        for(char ch: s)
            las[(int)(ch - 'a')] = pos++;
        int cnt = pos = 0;
        for(char ch: s) {
            if(!vis[(int)(ch - 'a')]) {
                while(cnt > 0 && las[(int)(s[cnt - 1] - 'a')] > pos && s[cnt - 1] > ch)
                    vis[(int)(s[--cnt] - 'a')] = 0;
                s[cnt++] = ch;
                vis[(int)(ch - 'a')] = 1;
            }
            ++pos;
        }
        s.resize(cnt);
        return s;
    }
};
