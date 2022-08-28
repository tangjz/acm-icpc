class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int r = (int)board.size();
        if(!r)
            return;
        int c = (int)board[0].size();
        function<void(int, int)> dfs = [&](int x, int y) {
            if(x < 0 || x >= r || y < 0 || y >= c || board[x][y] != 'O')
                return;
            board[x][y] = '!';
            dfs(x - 1, y);
            dfs(x, y - 1);
            dfs(x, y + 1);
            dfs(x + 1, y);
        };
        for(int i = 0; i < r; ++i) {
            dfs(i, 0);
            dfs(i, c - 1);
        }
        for(int j = 0; j < c; ++j) {
            dfs(0, j);
            dfs(r - 1, j);
        }
        for(auto &it: board)
            for(char &ch: it)
                if(ch != 'X')
                    ch = "XO"[ch == '!'];
    }
};
