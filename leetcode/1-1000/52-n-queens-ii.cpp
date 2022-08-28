class Solution {
    int n, all;
    int dfs(int dep, int col, int rc, int cr) {
        if(dep == n)
            return 1;
        int ret = 0;
        for(int msk = ~(col | rc | cr) & all, lbt; msk; msk ^= lbt) {
            lbt = msk & -msk;
            ret += dfs(dep + 1, col | lbt, (rc | lbt) >> 1, (cr | lbt) << 1);
        }
        return ret;
    }
public:
    int totalNQueens(int n) {
        this -> n = n;
        all = (1 << n) - 1;
        return dfs(0, 0, 0, 0);
    }
};
