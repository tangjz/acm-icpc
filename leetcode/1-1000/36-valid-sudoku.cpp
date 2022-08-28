class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        const int n = 9, m = 3;
        int row[n] = {}, col[n] = {}, blk[n] = {};
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                if(board[i][j] == '.')
                    continue;
                int msk = 1 << (board[i][j] - '0');
                int bid = (i / m) * m + (j / m);
                if(msk & row[i] || msk & col[j] || msk & blk[bid])
                    return 0;
                row[i] |= msk;
                col[j] |= msk;
                blk[bid] |= msk;
            }
        return 1;
    }
};
