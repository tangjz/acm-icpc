class Solution {
    static const int mod = (int)1e9 + 7;
    typedef long long LL;
    int dfs(vector<int> &nums, int sta, int len) {
        if(!len)
            return 1;
        vector<int> lft, rht;
        for(int i = 1; i < len; ++i)
            if(nums[sta + i] < nums[sta]) {
                lft.push_back(nums[sta + i]);
            } else {
                rht.push_back(nums[sta + i]);
            }
        int pos = sta + 1;
        for(int x : lft)
            nums[pos++] = x;
        int tmp = pos;
        for(int x : rht)
            nums[pos++] = x;
        return (LL)len * dfs(nums, sta + 1, (int)lft.size()) % mod * dfs(nums, tmp, (int)rht.size()) % mod;
    }
    int modInverse(int x) {
        int y = mod, u = 1, v = 0;
        while(x) {
            int q = y / x;
            tie(x, y) = make_pair(y - q * x, x);
            tie(u, v) = make_pair(v - q * u, u);
        }
        return v < 0 ? v + mod : v;
    }
public:
    int numOfWays(vector<int>& nums) {
        int ans = 1, n = (int)nums.size();
        for(int i = 2; i <= n; ++i)
            ans = (LL)ans * i % mod;
        ans = (LL)ans * modInverse(dfs(nums, 0, n)) % mod;
        (--ans) < 0 && (ans += mod);
        return ans;
    }
};
