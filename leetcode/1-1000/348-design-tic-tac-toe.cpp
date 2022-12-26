class TicTacToe {
    int n, rc[2], cr[2];
    vector<int> r[2], c[2];
public:
    TicTacToe(int n) {
        this -> n = n;
        rc[0] = rc[1] = cr[0] = cr[1] = 0;
        r[0].assign(n, 0);
        r[1].assign(n, 0);
        c[0].assign(n, 0);
        c[1].assign(n, 0);
    }

    int move(int row, int col, int player) {
        --player;
        if((++r[player][row]) == n)
            return ++player;
        if((++c[player][col]) == n)
            return ++player;
        if(row == col && (++rc[player]) == n)
            return ++player;
        if(row + col == n - 1 && (++cr[player]) == n)
            return ++player;
        // printf("rc %d %d cr %d %d\n", rc[0], rc[1], cr[0], cr[1]);
        return 0;
    }
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */
