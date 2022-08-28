class Solution {
    int rev(int x) {
        static char buf[11];
        int len = sprintf(buf, "%d", x);
        reverse(buf, buf + len);
        sscanf(buf, "%d", &x);
        return x;
    }
public:
    int countNicePairs(vector<int>& nums) {
        unordered_map<int, int> ctr;
        for(int x : nums)
            ++ctr[x - rev(x)];
        const int mod = (int)1e9 + 7;
        int ans = 0;
        for(auto &it : ctr)
            ans = (ans + it.second * (it.second - 1LL) / 2) % mod;
        return ans;
    }
};
