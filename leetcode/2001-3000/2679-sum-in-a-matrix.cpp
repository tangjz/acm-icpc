class Solution {
public:
    int matrixSum(vector<vector<int>>& mat) {
        int n = 0;
        vector<int> res;
        for(auto &row: mat) {
            int c = row.size();
            if(n < c) {
                n = c;
                res.resize(n);
            }
            sort(row.begin(), row.end(), greater<int>());
            for(int i = 0; i < n; ++i)
                res[i] = max(res[i], row[i]);
        }
        int ans = 0;
        for(int x: res)
            ans += x;
        return ans;
    }
};
