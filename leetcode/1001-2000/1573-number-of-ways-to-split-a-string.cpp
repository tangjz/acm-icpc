class Solution {
public:
    int numWays(string s) {
        int n = 0;
        vector<int> idx;
        for(char ch : s) {
            if(ch == '1')
                idx.push_back(n);
            ++n;
        }
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int ans = 0, m = (int)idx.size();
        if(!m) {
            ans = (n - 1LL) * (n - 2) / 2 % mod;
        } else if(m % 3 == 0) {
            ans = 1;
            for(int i = m / 3; i < m; i += m / 3)
                ans = (LL)ans * (idx[i] - idx[i - 1]) % mod;
        }
        return ans;
    }
};
