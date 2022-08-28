class Solution {
public:
    int longestSubsequence(string s, int k) {
        int n = s.size(), cnt = 0, val = 0;
        for(char ch: s)
            cnt += ch == '0';
        for(int i = 0; i < n; ++i) {
            char ch = s[n - 1 - i];
            if(ch == '0')
                continue;
            if(i >= 30)
                break;
            val |= 1 << i;
            if(val > k)
                break;
            ++cnt;
        }
        return cnt;
    }
};
