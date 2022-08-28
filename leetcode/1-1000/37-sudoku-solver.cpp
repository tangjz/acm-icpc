class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        const int BMSK = (1 << 9) - 1;
        static int lbt[BMSK + 2] = {};
        if(!lbt[0]) {
            lbt[0] = -1;
            for(int i = 1; i <= BMSK; ++i)
                lbt[i] = i & 1 ? 0 : (lbt[i >> 1] + 1);
        }
        const int maxn = 9, maxd = 3;
        int row[maxn] = {}, col[maxn] = {}, blk[maxn] = {};
        vector<vector<int> > pos;
        for(int i = 0; i < maxn; ++i)
            for(int j = 0; j < maxn; ++j) {
                int k = (i / maxd) * maxd + (j / maxd);
                if(board[i][j] == '.') {
                    pos.push_back({i, j, k});
                    continue;
                }
                int d = board[i][j] - '1';
                row[i] |= 1 << d;
                col[j] |= 1 << d;
                blk[k] |= 1 << d;
            }
        function<bool(int)> dfs = [&](int idx) -> bool {
            if(idx < 0)
                return 1;
            auto &vec = pos[idx];
            int i = vec[0], j = vec[1], k = vec[2];
            for(int msk, rem = BMSK ^ (row[i] | col[j] | blk[k]); rem; rem ^= msk) {
                msk = rem & -rem;
                row[i] ^= msk;
                col[j] ^= msk;
                blk[k] ^= msk;
                if(dfs(idx - 1)) {
                    board[i][j] = '1' + lbt[msk];
                    return 1;
                }
                row[i] ^= msk;
                col[j] ^= msk;
                blk[k] ^= msk;
            }
            return 0;
        };
        dfs(pos.size() - 1);
    }
};
