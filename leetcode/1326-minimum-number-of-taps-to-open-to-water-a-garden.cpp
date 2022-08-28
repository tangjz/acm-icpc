class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        const int INF = 0x3f3f3f3f;
        vector<int> lft(n + 1, INF);
        for(int i = 0; i <= n; ++i) {
            int d = ranges[i];
            if(!d)
                continue;
            int L = max(i - d, 0), R = min(i + d, n);
            lft[R] = min(lft[R], L);
        }
        for(int i = n - 1; i >= 0; --i)
            lft[i] = min(lft[i], lft[i + 1]);
        vector<int> dp(n + 1, INF);
        deque<int> pos;
        dp[0] = 0;
        pos.push_back(0);
        for(int i = 1; i <= n; ++i) {
            while(!pos.empty() && pos.front() < lft[i])
                pos.pop_front();
            if(pos.empty())
                continue;
            dp[i] = dp[pos.front()] + 1;
            while(!pos.empty() && dp[pos.back()] > dp[i])
                pos.pop_back();
            pos.push_back(i);
        }
        return dp[n] < INF ? dp[n] : -1;
    }
};
