class Solution {
public:
    int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight) {
        int n = boxes.size();
        vector<int> psum = {0}, dp(n + 1, INT_MAX);
        for(int i = 1; i < n; ++i)
            psum.push_back(psum.back() + (boxes[i - 1][0] != boxes[i][0]));
        deque<int> que;
        dp[0] = 0;
        for(int i = 1, j = 0, s = 0; i <= n; ++i) {
            s += boxes[i - 1][1];
            while(s > maxWeight)
                s -= boxes[j++][1];
            while(!que.empty() && (i - que.front() > maxBoxes || que.front() < j))
                que.pop_front();
            int cur = dp[i - 1] - psum[i - 1];
            while(!que.empty()) {
                int k = que.back(), pre = dp[k] - psum[k];
                if(pre < cur)
                    break;
                que.pop_back();
            }
            que.push_back(i - 1);
            int k = que.front();
            dp[i] = dp[k] + psum[i - 1] - psum[k] + 2;
        }
        return dp.back();
    }
};
