class Solution {
    pair<int, int> dfs(int L, int R, string const &pat, vector<int> const &pR) {
        while(pR[L] == R) {
            ++L;
            --R;
        }
        const int INF = 0x3f3f3f3f;
        int dp[2][2], cur = 0, pre = 1;
        memset(dp[cur], 0x3f, sizeof(dp[0]));
        vector<pair<int, int> > ops;
        bool fir = true;
        for(int pos = L; pos <= R; ) {
            int num[2], op[2];
            if(!fir) {
                char ch = pat[pos++];
                op[0] = ch != '&';
                op[1] = ch != '|';
            }
            if(pR[pos] != -1) {
                tie(num[0], num[1]) = dfs(pos, pR[pos], pat, pR);
                pos = pR[pos] + 1;
            } else {
                int x = pat[pos++] - '0';
                num[0] = x;
                num[1] = !x;
            }
            if(fir) {
                dp[cur][0] = num[0];
                dp[cur][1] = num[1];
                fir = 0;
                continue;
            }
            swap(cur, pre);
            memset(dp[cur], 0x3f, sizeof(dp[0]));
            for(int x = 0; x < 2; ++x) if(dp[pre][x] < INF)
                for(int j = 0; j < 2; ++j) if(op[j] < INF)
                    for(int k = 0; k < 2; ++k) if(num[k] < INF) {
                        int y = j ? x | k : x & k;
                        dp[cur][y] = min(dp[cur][y], dp[pre][x] + op[j] + num[k]);
                    }
        }
        return {dp[cur][0], dp[cur][1]};
    }
public:
    int minOperationsToFlip(string expression) {
        int n = expression.size();
        vector<int> pR(n, -1);
        stack<int> pos;
        for(int i = 0; i < n; ++i) {
            char ch = expression[i];
            if(ch == '(') {
                pos.push(i);
            } else if(ch == ')') {
                pR[pos.top()] = i;
                pos.pop();
            }
        }
        pair<int, int> cost = dfs(0, n - 1, expression, pR);
        return cost.first + cost.second;
    }
};
