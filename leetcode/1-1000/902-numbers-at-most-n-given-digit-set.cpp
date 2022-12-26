class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& seq, int n) {
        int m = seq.size();
        string num = to_string(n + 1);
        n = num.size();
        vector<int> ways(n + 1);
        ways[0] = 1;
        for(int i = 1; i <= n; ++i)
            ways[i] = ways[i - 1] * m;

        int ans = 0;
        for(int i = 0; i + 1 < n; ++i)
            ans += ways[n - 1 - i];
        for(int i = 0, j; i < n; ++i) {
            for(j = 0; j < m && seq[j][0] < num[i]; ++j) {
                ans += ways[n - 1 - i];
            }
            if(j == m || seq[j][0] != num[i])
                break;
        }
        return ans;
    }
};
