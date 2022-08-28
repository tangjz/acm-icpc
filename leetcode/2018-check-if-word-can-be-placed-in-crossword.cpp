class Solution {
public:
    bool placeWordInCrossword(vector<vector<char>>& board, string word) {
        int n = board.size(), m = board[0].size();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                if(board[i][j] == '#')
                    continue;
                if(!i || board[i - 1][j] == '#') {
                    int iR = i;
                    vector<int> pos;
                    for( ; iR < n && board[iR][j] != '#'; ++iR)
                        if(board[iR][j] != ' ')
                            pos.push_back(iR);
                    if(iR - i == word.size()) {
                        bool bad = false;
                        for(int x: pos)
                            if(word[x - i] != board[x][j]) {
                                bad = true;
                                break;
                            }
                        if(!bad)
                            return true;
                        bad = false;
                        for(int x: pos)
                            if(word[iR - 1 - x] != board[x][j]) {
                                bad = true;
                                break;
                            }
                        if(!bad)
                            return true;
                    }
                }
                if(!j || board[i][j - 1] == '#') {
                    int jR = j;
                    vector<int> pos;
                    for( ; jR < m && board[i][jR] != '#'; ++jR)
                        if(board[i][jR] != ' ')
                            pos.push_back(jR);
                    if(jR - j == word.size()) {
                        bool bad = false;
                        for(int y: pos)
                            if(word[y - j] != board[i][y]) {
                                bad = true;
                                break;
                            }
                        if(!bad)
                            return true;
                        bad = false;
                        for(int y: pos)
                            if(word[jR - 1 - y] != board[i][y]) {
                                bad = true;
                                break;
                            }
                        if(!bad)
                            return true;
                    }
                }
            }
        return false;
    }
};
