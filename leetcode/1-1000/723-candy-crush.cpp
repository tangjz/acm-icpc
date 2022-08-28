class Solution {
public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        int r = board.size(), c = board[0].size();
        bool upd = 1;
        while(upd) {
            upd = 0;
            vector<vector<bool> > vis(r, vector<bool>(c));
            for(int i = 0; i < r; ++i)
                for(int j = 0, k; j < c; ) {
                    for(k = j; j < c && board[i][j] == board[i][k]; ++j);
                    if(board[i][k] && j - k >= 3)
                        for(upd = 1; k < j; vis[i][k++] = 1);
                }
            for(int i = 0; i < c; ++i)
                for(int j = 0, k; j < r; ) {
                    for(k = j; j < r && board[j][i] == board[k][i]; ++j);
                    if(board[k][i] && j - k >= 3)
                        for(upd = 1; k < j; vis[k++][i] = 1);
                }
            for(int i = 0, j, k; i < c; ++i) {
                for(j = r - 1, k = j; j >= 0; --j)
                    if(!vis[j][i])
                        board[k--][i] = board[j][i];
                for( ; k >= 0; board[k--][i] = 0);
            }
        }
        return board;
    }
};
