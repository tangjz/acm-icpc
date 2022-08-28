class Solution {
public:
    vector<int> findSquare(vector<vector<int>>& mat) {
        int r = (int)mat.size();
        if(!r)
            return {};
        int c = (int)mat[0].size(), n = r * c;
        vector<int> best(3), pL(n), pU(n);
        for(int i = 0, idx = 0; i < r; ++i)
            for(int j = 0; j < c; ++j, ++idx) {
                if(mat[i][j])
                    continue;
                pL[idx] = 1 + (j > 0 ? pL[idx - 1] : 0);
                pU[idx] = 1 + (i > 0 ? pU[idx - c] : 0);
                for(int k = min(pL[idx], pU[idx]); k > best[0]; --k) {
                    int u = idx - (k - 1), v = idx - c * (k - 1);
                    if(pU[u] >= k && pL[v] >= k) {
                        best = {k, -i, -j};
                        break;
                    }
                }
            }
        if(!best[0])
            return {};
        return {-best[1] - best[0] + 1, -best[2] - best[0] + 1, best[0]};
    }
};
