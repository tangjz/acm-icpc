class Solution {
public:
    string tictactoe(vector<string>& board) {
        int n = board.size(), rc = 0, cr = 0, rem = 0;
        vector<int> row(n), col(n);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                int sgn = (board[i][j] == 'X') - (board[i][j] == 'O');
                row[i] += sgn;
                col[j] += sgn;
                if(i == j)
                    rc += sgn;
                if(i + j == n - 1)
                    cr += sgn;
                rem += !sgn;
            }
        int low = min(min(rc, *min_element(row.begin(), row.end())), min(cr, *min_element(col.begin(), col.end()))), upp = max(max(rc, *max_element(row.begin(), row.end())), max(cr, *max_element(col.begin(), col.end())));
        if(upp == n)
            return "X";
        if(low == -n)
            return "O";
        return rem ? "Pending" : "Draw";
    }
};
