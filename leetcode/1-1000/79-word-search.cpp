class Solution {
    bool dfs(int p, int x, int y, vector<vector<char>>& board, string &word) {
        if(x < 0 || x >= (int)board.size() || y < 0 || y >= (int)board[0].size() || word[p] != board[x][y])
            return 0;
        if(p == (int)word.size() - 1)
            return 1;
        board[x][y] = '*';
        for(int dx = -1; dx <= 1; ++dx)
            for(int dy = -1; dy <= 1; ++dy)
                if(!dx != !dy && dfs(p + 1, x + dx, y + dy, board, word))
                    return 1;
        board[x][y] = word[p];
        return 0;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = (int)board.size(), m = (int)board[0].size();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(dfs(0, i, j, board, word))
                    return 1;
        return 0;
    }
};
