class Solution {
public:
    int minSwaps(string s) {
        int cnt[2] = {};
        for(char ch: s)
            ++cnt[(int)(ch - '0')];
        int n = cnt[0] + cnt[1], ans = n + 1;
        for(int i = 0; i < 2; ++i) {
            if(cnt[i] != ((n + 1) >> 1))
                continue;
            int diff = 0;
            char cur = '0' + i;
            for(char ch: s) {
                diff += ch != cur;
                cur = '1' - cur + '0';
            }
            ans = min(ans, diff >> 1);
        }
        return ans <= n ? ans : -1;
    }
};
