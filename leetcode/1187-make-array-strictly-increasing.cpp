class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        vector<int> que;
        for(int x: arr1)
            que.push_back(x);
        for(int x: arr2)
            que.push_back(x);
        sort(que.begin(), que.end());
        que.erase(unique(que.begin(), que.end()), que.end());
        int m = que.size();
        vector<int> ctr(m);
        for(int &x: arr2) {
            x = lower_bound(que.begin(), que.end(), x) - que.begin();
            ctr[x] = 1;
        }
        for(int i = 1; i < m; ++i)
            ctr[i] += ctr[i - 1];
        int n = arr1.size(), ans = ctr[m - 1] < n ? INT_MAX : n;
        vector<int> dp(n, INT_MAX);
        for(int i = 0; i < n; ++i) {
            int &x = arr1[i];
            x = lower_bound(que.begin(), que.end(), x) - que.begin();
            if((x > 0 ? ctr[x - 1] : 0) >= i)
                dp[i] = min(dp[i], i);
            for(int j = 0, y; j < i; ++j)
                if(dp[j] < INT_MAX && x > (y = arr1[j]) && ctr[x - 1] - ctr[y] >= i - j - 1)
                    dp[i] = min(dp[i], dp[j] + i - j - 1);
            if(dp[i] < INT_MAX && ctr[m - 1] - ctr[x] >= (n - 1 - i))
                ans = min(ans, dp[i] + n - 1 - i);
        }
        return ans < INT_MAX ? ans : -1;
    }
};
