class Solution {
public:
    bool isSubsequence(string s, string t) {
        int pos = 0, len = (int)s.size();
        for(char ch : t)
            if(pos < len && s[pos] == ch)
                ++pos;
        return pos == len;
    }
};
