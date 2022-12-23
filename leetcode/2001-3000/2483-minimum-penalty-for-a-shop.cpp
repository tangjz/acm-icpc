class Solution {
public:
    int bestClosingTime(string s) {
        int n = s.size(), ans, pos, cur = 0;
        for(int i = 0; i < n; ++i)
            cur += s[i] == 'Y';
        ans = cur;
        pos = 0;
        for(int i = 0; i < n; ++i) {
            cur -= s[i] == 'Y';
            cur += s[i] == 'N';
            if(ans > cur) {
                ans = cur;
                pos = i + 1;
            }
        }
        return pos;
    }
};
