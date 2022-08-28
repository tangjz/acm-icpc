class Solution {
    int check(vector<string> chessboard, int sx, int sy) {
        // printf("check %d %d\n", sx, sy);
        int ans = 0, r = chessboard.size(), c = chessboard[0].size();
        queue<pair<int, int> > que;
        chessboard[sx][sy] = 'X';
        que.push({sx, sy});
        while(!que.empty()) {
            int ux, uy;
            tie(ux, uy) = que.front();
            que.pop();
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx && !dy)
                        continue;
                    int vx = ux + dx, vy = uy + dy, ctr = 0;
                    for( ; vx >= 0 && vx < r && vy >= 0 && vy < c && chessboard[vx][vy] == 'O'; vx += dx, vy += dy, ++ctr);
                    if(!ctr || vx < 0 || vx >= r || vy < 0 || vy >= c || chessboard[vx][vy] != 'X')
                        continue;
                    // printf("found (%d, %d) (%d, %d): %d\n", ux, uy, vx, vy, ctr);
                    while(ctr--) {
                        vx -= dx;
                        vy -= dy;
                        chessboard[vx][vy] = 'X';
                        que.push({vx, vy});
                        ++ans;
                    }
                }
        }
        return ans;
    }
public:
    int flipChess(vector<string>& chessboard) {
        int ans = 0, r = chessboard.size(), c = chessboard[0].size();
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                if(chessboard[i][j] != '.')
                    continue;
                bool good = 0;
                for(int dx = -1; !good && dx <= 1; ++dx)
                    for(int dy = -1; !good && dy <= 1; ++dy) {
                        int ii = i + dx, jj = j + dy;
                        good |= ii >= 0 && ii < r && jj >= 0 && jj < c && chessboard[ii][jj] == 'O';
                    }
                if(good)
                    ans = max(ans, check(chessboard, i, j));
            }
        return ans;
    }
};
