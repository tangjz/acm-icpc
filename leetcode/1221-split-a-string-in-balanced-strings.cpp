class Solution {
public:
    int balancedStringSplit(string s) {
        int ans = 0, cnt = 0;
        for(char ch: s) {
            cnt += ch == 'L' ? 1 : -1;
            ans += !cnt;
        }
        return ans;
    }
};
