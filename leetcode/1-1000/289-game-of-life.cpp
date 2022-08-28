class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int r = (int)board.size();
        if(!r)
            return;
        int c = (int)board[0].size();
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                bool alive = board[i][j] & 1;
                int cnt = 0;
                for(int dx = -1; dx <= 1; ++dx) {
                    int x = i + dx;
                    if(x < 0 || x >= r)
                        continue;
                    for(int dy = -1; dy <= 1; ++dy) {
                        int y = j + dy;
                        if(y < 0 || y >= c)
                            continue;
                        cnt += board[x][y] & 1;
                    }
                }
                if(cnt == 3 || cnt - alive == 3)
                    board[i][j] |= 2;
            }
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                board[i][j] >>= 1;
    }
};
