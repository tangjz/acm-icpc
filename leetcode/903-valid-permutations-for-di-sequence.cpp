class Solution {
public:
    int numPermsDISequence(string s) {
        typedef long long LL;
        static const int mod = (int)1e9 + 7;
        int n = s.size() + 1;
        vector<int> dp = {1};
        for(int i = 1; i < n; ++i) {
            dp.push_back(0);
            int sum = 0;
            if(s[i - 1] == 'D') {
                for(int j = i; j >= 0; --j) {
                    (sum += dp[j]) >= mod && (sum -= mod);
                    dp[j] = sum;
                }
            } else {
                for(int j = 0; j <= i; ++j) {
                    int tmp = sum;
                    (sum += dp[j]) >= mod && (sum -= mod);
                    dp[j] = tmp;
                }
            }
        }
        int sum = 0;
        for(int i = 0; i < n; ++i)
            (sum += dp[i]) >= mod && (sum -= mod);
        return sum;
    }
};
