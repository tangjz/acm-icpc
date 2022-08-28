class Solution {
    int n, all;
    vector<string> grids;
    vector<vector<string> > solutions;
    void dfs(int dep, int col, int rc, int cr) {
        if(dep == n) {
            solutions.push_back(grids);
            return;
        }
        for(int msk = ~(col | rc | cr) & all, lbt; msk; msk ^= 1 << lbt) {
            lbt = __builtin_ctz(msk & -msk);
            grids[dep][lbt] = 'Q';
            dfs(dep + 1, col | (1 << lbt), (rc | (1 << lbt)) >> 1, (cr | (1 << lbt)) << 1);
            grids[dep][lbt] = '.';
        }
    }
public:
    vector<vector<string> > solveNQueens(int n) {
        this -> n = n;
        all = (1 << n) - 1;
        string row = "";
        for(int i = 0; i < n; ++i)
            row += '.';
        vector<string>(n, row).swap(grids);
        vector<vector<string> >().swap(solutions);
        dfs(0, 0, 0, 0);
        return solutions;
    }
};
