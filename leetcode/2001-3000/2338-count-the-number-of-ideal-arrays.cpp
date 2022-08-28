class Solution {
public:
    int idealArrays(int n, int m) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int ans = 0;
        vector<int> inv = {0, 1};
        for(int i = 1; i <= m; ++i) {
            int ways = 1;
            for(int j = 2, tmp = i; j <= tmp; ++j) {
                if(j * j > tmp)
                    j = tmp;
                int e = 0;
                for( ; tmp % j == 0; tmp /= j, ++e);
                if(!e)
                    continue;
                for(int k = 1; k <= e; ++k) {
                    if(k == inv.size())
                        inv.push_back(mod - (int)(mod / k * (LL)inv[mod % k] % mod));
                    ways = (LL)ways * (n - 1 + k) % mod * inv[k] % mod;
                }
            }
            ans = (ans + ways) % mod;
        }
        return ans;
    }
};
