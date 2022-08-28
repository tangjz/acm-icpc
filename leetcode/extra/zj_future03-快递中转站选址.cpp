class Solution {
public:
    int buildTransferStation(vector<vector<int>>& area) {
        int r = area.size(), c = area[0].size();
        vector<int> row(r), col(c);
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                // tot += area[i][j];
                row[i] += area[i][j];
                col[j] += area[i][j];
            }
        int ans0 = INT_MAX, ans1 = INT_MAX;
        for(int i = 0; i < r; ++i) {
            int sum = 0;
            for(int j = 0; j < r; ++j) {
                sum += abs(i - j) * row[j];
            }
            ans0 = min(ans0, sum);
        }
        for(int i = 0; i < c; ++i) {
            int sum = 0;
            for(int j = 0; j < c; ++j) {
                sum += abs(i - j) * col[j];
            }
            ans1 = min(ans1, sum);
        }
        return ans0 + ans1;
    }
};
