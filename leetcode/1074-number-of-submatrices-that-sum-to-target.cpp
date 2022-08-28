class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& mat, int target) {
        int n = mat.size(), m = mat[0].size(), ans = 0;
        unordered_map<int, int> ctr;
        for(int i = 0; i < n; ++i) {
            vector<int> psum(m + 1);
            for(int j = i; j < n; ++j) {
                ctr.clear();
                ++ctr[0];
                for(int k = 0, c = 0; k < m; ++k) {
                    c += mat[j][k];
                    int cur = psum[k + 1] += c;
                    auto it = ctr.find(cur - target);
                    if(it != ctr.end())
                        ans += it -> second;
                    ++ctr[cur];
                }
            }
        }
        return ans;
    }
};
