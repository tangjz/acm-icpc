class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = s.length();
        vector<int> psum(n + 1), pL(n + 2), pR(n + 2);
        for(int i = 1; i <= n; ++i) {
            bool ok = s[i - 1] == '*';
            psum[i] = psum[i - 1] + ok;
            pL[i] = ok ? pL[i - 1] : i;
        }
        pR[n + 1] = n + 1;
        for(int i = n; i >= 1; --i) {
            bool ok = s[i - 1] == '*';
            pR[i] = ok ? pR[i + 1] : i;
        }
        vector<int> ret;
        for(auto &it: queries) {
            int L = pR[it[0] + 1];
            int R = pL[it[1] + 1];
            int ans = L <= R ? psum[R] - psum[L - 1] : 0;
            ret.push_back(ans);
        }
        return ret;
    }
};
