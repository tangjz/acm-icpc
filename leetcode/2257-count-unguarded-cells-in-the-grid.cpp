class Solution {
public:
    int countUnguarded(int r, int c, vector<vector<int>>& A, vector<vector<int>>& B) {
        int n = r * c;
        vector<int> occ(n);
        for(auto &it: A)
            occ[it[0] * c + it[1]] = -1;
        for(auto &it: B)
            occ[it[0] * c + it[1]] = -2;
        for(int i = 0; i < r; ++i) {
            bool ok = 0;
            for(int j = 0, idx = i * c; j < c; ++j, ++idx) {
                if(occ[idx] < 0) {
                    ok = occ[idx] == -1;
                    continue;
                }
                occ[idx] |= ok;
            }
            ok = 0;
            for(int j = c - 1, idx = (i + 1) * c - 1; j >= 0; --j, --idx) {
                if(occ[idx] < 0) {
                    ok = occ[idx] == -1;
                    continue;
                }
                occ[idx] |= ok;
            }
        }
        for(int j = 0; j < c; ++j) {
            bool ok = 0;
            for(int i = 0, idx = j; i < r; ++i, idx += c) {
                if(occ[idx] < 0) {
                    ok = occ[idx] == -1;
                    continue;
                }
                occ[idx] |= !!ok << 1;
            }
            for(int i = r - 1, idx = i * c + j; i >= 0; --i, idx -= c) {
                if(occ[idx] < 0) {
                    ok = occ[idx] == -1;
                    continue;
                }
                occ[idx] |= !!ok << 1;
            }
        }
        int ans = 0;
        for(int x: occ)
            ans += !x;
        return ans;
    }
};
