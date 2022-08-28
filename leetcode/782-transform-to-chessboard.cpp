class Solution {
public:
    int movesToChessboard(vector<vector<int>>& board) {
        int n = board.size();
        vector<int> row(n), col(n);
        vector<vector<int> > rows(n), cols(n);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                row[i] += board[i][j];
                col[j] += board[i][j];
                rows[i].push_back(board[i][j]);
                cols[j].push_back(board[i][j]);
            }
        sort(rows.begin(), rows.end());
        rows.erase(unique(rows.begin(), rows.end()), rows.end());
        if(rows.size() != 2)
            return -1;
        sort(cols.begin(), cols.end());
        cols.erase(unique(cols.begin(), cols.end()), cols.end());
        if(cols.size() != 2)
            return -1;
        auto calc = [&](vector<int> &perm) {
            int ret = 0;
            for(int i = 0; i < n; ++i)
                for(int j = i + 1; j < n; ++j)
                    ret += perm[i] > perm[j];
            return ret;
        };
        int ans = 0;
        vector<int> seq(n);
        if(n & 1) {
            int v = n >> 1, u = n - v, tmp = 0;
            bool bad = 0;
            for(int i = 0, j = 0, k = 1; i < n; ++i) {
                int typ;
                if(row[i] == u) {
                    if(j >= n) {
                        bad = 1;
                        break;
                    }
                    typ = 0;
                    j += 2;
                } else if(row[i] == v) {
                    if(k >= n) {
                        bad = 1;
                        break;
                    }
                    typ = 1;
                    k += 2;
                } else {
                    return -1;
                }
                tmp += typ != (i & 1);
            }
            if(bad) {
                swap(u, v);
                tmp = 0;
                for(int i = 0, j = 0, k = 1; i < n; ++i) {
                    int typ;
                    if(row[i] == u) {
                        if(j >= n)
                            return -1;
                        typ = 0;
                        j += 2;
                    } else if(row[i] == v) {
                        if(k >= n)
                            return -1;
                        typ = 1;
                        k += 2;
                    } else {
                        return -1;
                    }
                    tmp += typ != (i & 1);
                }
            }
            ans += tmp >> 1;
            tmp = 0;
            for(int i = 0, j = 0, k = 1; i < n; ++i) {
                int typ;
                if(col[i] == u) {
                    if(j >= n)
                        return -1;
                    typ = 0;
                    j += 2;
                } else if(col[i] == v) {
                    if(k >= n)
                        return -1;
                    typ = 1;
                    k += 2;
                } else {
                    return -1;
                }
                tmp += typ != (i & 1);
            }
            ans += tmp >> 1;
        } else {
            int half = n >> 1, tmp = 0;
            for(int i = 0, j = 0, k = 1; i < n; ++i) {
                if(row[i] != half)
                    return -1;
                if(board[i][0]) {
                    if(j >= n)
                        return -1;
                    j += 2;
                } else {
                    if(k >= n)
                        return -1;
                    k += 2;
                }
                tmp += board[i][0] != (i & 1);
            }
            ans += min(tmp, n - tmp) >> 1;
            tmp = 0;
            for(int i = 0, j = 0, k = 1; i < n; ++i) {
                if(col[i] != half)
                    return -1;
                if(board[0][i]) {
                    if(j >= n)
                        return -1;
                    j += 2;
                } else {
                    if(k >= n)
                        return -1;
                    k += 2;
                }
                tmp += board[0][i] != (i & 1);
            }
            ans += min(tmp, n - tmp) >> 1;
        }
        return ans;
    }
};
