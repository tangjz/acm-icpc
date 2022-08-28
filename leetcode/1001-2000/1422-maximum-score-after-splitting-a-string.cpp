class Solution {
public:
    int maxScore(string s) {
        int cnt = 0;
        for(char ch : s)
            cnt += ch == '1';
        int ans = 0, pos = 0, len = (int)s.length();
        for(char ch : s) {
            cnt -= ch == '1';
            cnt += ch == '0';
            if(pos < len - 1)
                ans = max(ans, cnt);
            ++pos;
        }
        return ans;
    }
};
