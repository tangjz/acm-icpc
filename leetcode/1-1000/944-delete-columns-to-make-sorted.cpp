class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int ans = 0, n = strs.size(), m = strs[0].size();
        for(int i = 0; i < m; ++i) {
            bool chk = 1;
            for(int j = 1; chk && j < n; ++j)
                chk &= strs[j - 1][i] <= strs[j][i];
            ans += !chk;
        }
        return ans;
    }
};
