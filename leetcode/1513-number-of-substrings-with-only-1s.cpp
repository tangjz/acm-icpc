class Solution {
public:
    int numSub(string s) {
        const int mod = (int)1e9 + 7;
        int ans = 0, cnt = 0;
        for(char ch : s)
            if(ch == '1') {
                (ans += ++cnt) >= mod && (ans -= mod);
            } else {
                cnt = 0;
            }
        return ans;
    }
};
