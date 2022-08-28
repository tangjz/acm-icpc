class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size(), m = 0;
        for(int i = 0, j; i < n; ) {
            for(j = i; i < n && chars[j] == chars[i]; ++i);
            chars[m++] = chars[j];
            if(i - j == 1)
                continue;
            int tp = m;
            for(int v = i - j; v > 0; chars[tp++] = '0' + (v % 10), v /= 10);
            reverse(chars.begin() + m, chars.begin() + tp);
            m = tp;
        }
        chars.resize(m);
        return m;
    }
};
