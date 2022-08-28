class Solution {
public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int r = board.size(), c = board[0].size();
        int sx = click[0], sy = click[1];
        if(board[sx][sy] == 'M') {
            board[sx][sy] = 'X';
            return board;
        }
        queue<pair<int, int> > que;
        auto upd = [&](int x, int y) {
            if(x < 0 || x >= r || y < 0 || y >= c || board[x][y] != 'E')
                return;
            // printf("check %d %d\n", x, y);
            int cnt = 0;
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    int xx = x + dx, yy = y + dy;
                    if(xx < 0 || xx >= r || yy < 0 || yy >= c || board[xx][yy] != 'M')
                        continue;
                    ++cnt;
                }
            if(!cnt) {
                board[x][y] = 'B';
                que.push({x, y});
            } else {
                board[x][y] = '0' + cnt;
            }
        };
        upd(sx, sy);
        while(!que.empty()) {
            int x, y;
            tie(x, y) = que.front();
            que.pop();
            // printf("ext %d %d\n", x, y);
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy)
                    upd(x + dx, y + dy);
        }
        return board;
    }
};
