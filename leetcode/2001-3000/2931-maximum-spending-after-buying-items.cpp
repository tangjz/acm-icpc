class Solution {
public:
    long long maxSpending(vector<vector<int>>& mat) {
        typedef long long LL;
        int r = mat.size(), c = mat[0].size(), n = r * c;
        LL ans = 0;
        for(int i = 1; i <= n; ++i) {
            int p = -1;
            for(int j = 0; j < r; ++j)
                if(!mat[j].empty() && (p == -1 || mat[j].back() < mat[p].back()))
                    p = j;
            ans += (LL)i * mat[p].back();
            mat[p].pop_back();
        }
        return ans;
    }
};
