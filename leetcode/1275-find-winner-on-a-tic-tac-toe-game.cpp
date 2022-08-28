class Solution {
public:
    string tictactoe(vector<vector<int>>& moves) {
        const int maxd = 3;
        vector<vector<char> > game(maxd, vector<char>(maxd, '\0'));
        auto isEnd = [&]() -> bool {
            for(int i = 0; i < maxd; ++i) {
                bool chk = game[i][0] != '\0';
                for(int j = 1; j < maxd && chk; ++j)
                    chk &= game[i][j] == game[i][0];
                if(chk)
                    return 1;
            }
            for(int i = 0; i < maxd; ++i) {
                bool chk = game[0][i] != '\0';
                for(int j = 1; j < maxd && chk; ++j)
                    chk &= game[j][i] == game[0][i];
                if(chk)
                    return 1;
            }
            {
                bool chk = game[0][0] != '\0';
                for(int j = 1; j < maxd && chk; ++j)
                    chk &= game[j][j] == game[0][0];
                if(chk)
                    return 1;
            }
            {
                bool chk = game[0][maxd - 1] != '\0';
                for(int j = 1; j < maxd && chk; ++j)
                    chk &= game[j][maxd - 1 - j] == game[0][maxd - 1];
                if(chk)
                    return 1;
            }
            return 0;
        };
        char cur = 'X';
        for(auto &it : moves) {
            game[it[0]][it[1]] = cur;
            if(isEnd())
                return cur == 'X' ? "A" : "B";
            cur = "XO"[cur == 'X'];
        }
        return (int)moves.size() == maxd * maxd ? "Draw" : "Pending";
    }
};
