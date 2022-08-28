class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& A, vector<vector<int>>& B) {
        const int maxv = 100;
        int n = A.size(), m = B.size();
        sort(A.begin(), A.end());
        reverse(A.begin(), A.end());
        vector<int> ord(m), ans(m), bits(maxv + 1);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return B[u][0] > B[v][0];
        });
        for(int i = 0, j = 0; i < m; ++i) {
            int u = ord[i];
            for( ; j < n && A[j][0] >= B[u][0]; ++j)
                for(int x = A[j][1]; x > 0; x -= x & -x)
                    ++bits[x];
            for(int x = B[u][1]; x <= maxv; x += x & -x)
                ans[u] += bits[x];
        }
        return ans;
    }
};
