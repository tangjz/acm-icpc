class Solution {
public:
    int minTimeToType(string word) {
        int ans = 0, las = 0;
        for(char ch: word) {
            int cur = ch - 'a';
            int dt = abs(las - cur);
            ans += 1 + min(dt, 26 - dt);
            las = cur;
        }
        return ans;
    }
};
