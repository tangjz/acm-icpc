class Solution {
public:
    int concatenatedBinary(int n) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int pw = 2, val = 0, ans = 0;
        vector<int> dig = {0};
        for(int i = 1; i <= n; ++i) {
            int j = 0, tp = 1;
            for( ; j < (int)dig.size() && dig[j]; ++j, tp = 2LL * tp % mod) {
                dig[j] = 0;
                (val -= tp) < 0 && (val += mod);
            }
            if(j < (int)dig.size()) {
                dig[j] = 1;
            } else {
                dig.push_back(1);
                pw = 2LL * pw % mod;
            }
            (val += tp) >= mod && (val -= mod);
            ans = ((LL)ans * pw + val) % mod;
        }
        return ans;
    }
};
