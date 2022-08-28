class Solution {
public:
    int minimumDeletions(string s) {
        int n = s.size();
        vector<int> pre(n), suf(n);
        for(int i = 0; i < n; ++i) {
            pre[i] = (s[i] == 'b') + (i > 0 ? pre[i - 1] : 0);
        }
        for(int i = n - 1; i >= 0; --i) {
            suf[i] = (s[i] == 'a') + (i + 1 < n ? suf[i + 1] : 0);
        }
        int ans = n;
        for(int i = 0; i <= n; ++i) { // [0, i) [i, n)
            int cnt = (i > 0 ? pre[i - 1] : 0) + (i < n ? suf[i] : 0);
            ans = min(ans, cnt);
        }
        return ans;
    }
};
