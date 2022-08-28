class Solution {
public:
    int minimumLines(vector<vector<int>>& seq) {
        typedef long long LL;
        int n = seq.size(), m = 0;
        sort(seq.begin(), seq.end());
        for(int i = 0; i < n; ++i)
            if(m < 2 || (LL)(seq[m - 1][0] - seq[m - 2][0]) * (seq[i][1] - seq[m - 1][1]) != (LL)(seq[m - 1][1] - seq[m - 2][1]) * (seq[i][0] - seq[m - 1][0])) {
                seq[m++] = seq[i];
            } else {
                seq[m - 1] = seq[i];
            }
        return m - 1;
    }
};
