class Solution {
    int check(string s, char p) {
        int ans = 0, cnt = 0;
        for(char ch: s) {
            if(ch == p) {
                ++cnt;
            } else {
                cnt = 0;
            }
            ans = max(ans, cnt);
        }
        return ans;
    }
public:
    bool checkZeroOnes(string s) {
        return check(s, '1') > check(s, '0');
    }
};
