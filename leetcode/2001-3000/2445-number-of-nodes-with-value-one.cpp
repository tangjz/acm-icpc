class Solution {
public:
    int numberOfNodes(int n, vector<int>& queries) {
        int ans = 0;
        vector<bool> f(n + 1);
        for(int x: queries)
            f[x] = !f[x];
        for(int x = 1; x <= n; ++x) {
            if(x > 1)
                f[x] = f[x] ^ f[x >> 1];
            ans += f[x];
        }
        return ans;
    }
};
