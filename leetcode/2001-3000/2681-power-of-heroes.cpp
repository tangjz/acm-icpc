class Solution {
public:
    int sumOfPower(vector<int>& A) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int ans = 0, pre = 0;
        sort(A.begin(), A.end());
        for(int x: A) {
            ans = (ans + (LL)(pre + x) * x % mod * x) % mod;
            pre = (2LL * pre + x) % mod;
            // printf("pre %d x %d ans %d\n", pre, x, ans);
        }
        return ans;
    }
};
