class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int n = (int)board.size(), m = (int)board[0].size();
        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                ans += board[i][j] == 'X' && (!i || board[i - 1][j] != 'X') && (!j || board[i][j - 1] != 'X');
        return ans;
    }
};
