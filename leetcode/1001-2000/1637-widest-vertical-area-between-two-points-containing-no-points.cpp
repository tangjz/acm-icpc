class Solution {
public:
    int maxWidthOfVerticalArea(vector<vector<int>>& seq) {
        int n = seq.size(), ans = 0;
        sort(seq.begin(), seq.end());
        for(int i = 1; i < n; ++i)
            ans = max(ans, seq[i][0] - seq[i - 1][0]);
        return ans;
    }
};
