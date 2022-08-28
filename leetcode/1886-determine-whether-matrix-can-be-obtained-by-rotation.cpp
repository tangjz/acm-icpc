class Solution {
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        int n = mat.size();
        for(int t = 0; t < 4; ++t) {
            bool chk = true;
            for(int i = 0; chk && i < n; ++i)
                for(int j = 0; chk && j < n; ++j)
                    chk &= mat[i][j] == target[i][j];
            if(chk)
                return true;
            vector<vector<int> > nxt(n, vector<int>(n));
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j)
                    nxt[i][j] = mat[n - 1 - j][i];
            mat = move(nxt);
        }
        return false;
    }
};
