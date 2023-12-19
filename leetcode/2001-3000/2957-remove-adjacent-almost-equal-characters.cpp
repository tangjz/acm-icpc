class Solution {
public:
    int removeAlmostEqualCharacters(string word) {
        int dp[2][2] = {}, cur = 0, pre = 1;
        char u = word.back(), v;
        word.pop_back();
        dp[cur][0] = 0;
        dp[cur][1] = 1;
        while(!word.empty()) {
            v = word.back();
            word.pop_back();
            swap(cur, pre);
            dp[cur][0] = dp[pre][1];
            if(abs(u - v) > 1)
                dp[cur][0] = min(dp[cur][0], dp[pre][0]);
            dp[cur][1] = min(dp[pre][0], dp[pre][1]) + 1;
            u = v;
        }
        return min(dp[cur][0], dp[cur][1]);
    }
};
