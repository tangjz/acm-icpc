class Solution {
public:
    bool checkMove(vector<vector<char>>& board, int rMove, int cMove, char color) {
        int n = board.size(), m = board[0].size();
        for(int dx = -1; dx <= 1; ++dx)
            for(int dy = -1; dy <= 1; ++dy) {
                if(!dx && !dy)
                    continue;
                int x = rMove, y = cMove;
                bool fir = 1;
                // printf("dx %d dy %d: ", dx, dy);
                while(true) {
                    x += dx;
                    y += dy;
                    // printf("(%d, %d) ", x, y);
                    if(x < 0 || x >= n || y < 0 || y >= m || board[x][y] == '.')
                        break;
                    if(board[x][y] == color) {
                        if(!fir)
                            return 1;
                        break;
                    }
                    fir = 0;
                }
                // puts("");
            }
        return 0;
    }
};
