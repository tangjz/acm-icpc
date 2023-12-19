class Solution {
public:
    vector<int> sameEndSubstringCount(string s, vector<vector<int>>& queries) {
        int n = s.size(), m = queries.size();
        vector<int> psum(n + 1), ans(m);
        for(char ch = 'a'; ch <= 'z'; ++ch) {
            for(int i = 0; i < n; ++i)
                psum[i + 1] = psum[i] + (s[i] == ch);
            for(int i = 0; i < m; ++i) {
                int L = queries[i][0], R = queries[i][1];
                int c = psum[R + 1] - psum[L];
                ans[i] += c * (c + 1) / 2;
            }
        }
        return ans;
    }
};
