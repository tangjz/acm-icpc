class Solution {
public:
    int paintingPlan(int n, int k) {
        vector<int> bin(n + 1);
        bin[0] = 1;
        for(int i = 1; i <= n; ++i) {
            bin[i] = 1;
            for(int j = i - 1; j > 0; --j)
                bin[j] += bin[j - 1];
        }
        int ans = 0;
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= n; ++j) {
                if(max(i, j) == n && min(i, j) < n)
                    continue;
                if((i + j) * n - i * j == k)
                    ans += bin[i] * bin[j];
            }
        return ans;
    }
};
