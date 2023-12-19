class Solution {
public:
    int maxProfit(vector<int>& prices, vector<int>& profits) {
        int n = prices.size();
        vector<int> que(prices.begin(), prices.end()), ans(profits.begin(), profits.end());
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int m = que.size();
        vector<int> bits(m + 1);
        for(int i = 0; i < n; ++i) {
            prices[i] = lower_bound(que.begin(), que.end(), prices[i]) - que.begin() + 1;
            int res = 0;
            for(int x = prices[i] - 1; x > 0; x -= x & -x)
                res = max(res, bits[x]);
            ans[i] = !res ? -1 : ans[i] + res;
            for(int x = prices[i]; x <= m; x += x & -x)
                bits[x] = max(bits[x], profits[i]);
        }
        int ret = -1;
        bits.assign(m + 1, 0);
        for(int i = n - 1; i >= 0; --i) {
            int res = 0;
            for(int x = prices[i] + 1; x <= m; x += x & -x)
                res = max(res, bits[x]);
            ans[i] = ans[i] == -1 || !res ? -1 : ans[i] + res;
            ret = max(ret, ans[i]);
            for(int x = prices[i]; x > 0; x -= x & -x)
                bits[x] = max(bits[x], profits[i]);
        }
        return ret;
    }
};
