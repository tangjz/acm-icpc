class Solution {
    struct Info {
        static const int mod = (int)1e9 + 7;
        int val, cnt;
        Info() { val = cnt = -1; }
        void operator += (Info const &t) {
            if(t.cnt < 0)
                return;
            if(val < t.val) {
                val = t.val;
                cnt = 0;
            }
            if(val == t.val)
                (cnt += t.cnt) >= mod && (cnt -= mod);
        }
    } ;
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = (int)board.size();
        vector<vector<Info> > dp(n, vector<Info>(n));
        dp[0][0].val = 0;
        dp[0][0].cnt = 1;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                char ch = board[i][j];
                if(ch == 'X')
                    continue;
                int adt = ch >= '1' && ch <= '9' ? ch - '0' : 0;
                Info tmp;
                if(i > 0) {
                    tmp = dp[i - 1][j];
                    tmp.val += adt;
                    dp[i][j] += tmp;
                    if(j > 0) {
                        tmp = dp[i - 1][j - 1];
                        tmp.val += adt;
                        dp[i][j] += tmp;
                    }
                }
                if(j > 0) {
                    tmp = dp[i][j - 1];
                    tmp.val += adt;
                    dp[i][j] += tmp;
                }
            }
        Info ans = dp[n - 1][n - 1];
        if(ans.cnt < 0)
            return {0, 0};
        return {ans.val, ans.cnt};
    }
};
