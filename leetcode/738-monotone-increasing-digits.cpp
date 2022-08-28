class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        string s = to_string(n + 1);
        int len = s.size(), pos = 0;
        for(int i = 0; i < len; ++i) {
            if(s[i] > '0' && (!i || s[i - 1] < s[i]))
                pos = i;
            if(i > 0 && s[i - 1] > s[i])
                break;
        }
        --s[pos];
        for( ; (++pos) < len; s[pos] = '9');
        return stoi(s);
    }
};
