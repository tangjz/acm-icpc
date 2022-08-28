class Solution {
public:
    int numRookCaptures(vector<vector<char>>& board) {
        const int maxd = 8;
        for(int x = 0; x < maxd; ++x)
            for(int y = 0; y < maxd; ++y) {
                if(board[x][y] != 'R')
                    continue;
                int ret = 0;
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        if(!dx == !dy)
                            continue;
                        for(int xx = x, yy = y; (xx += dx) >= 0 && xx < maxd && (yy += dy) >= 0 && yy < maxd; ){
                            if(board[xx][yy] != '.') {
                                ret += board[xx][yy] == 'p';
                                break;
                            }
                        }
                    }
                return ret;
            }
        return 0;
    }
};
