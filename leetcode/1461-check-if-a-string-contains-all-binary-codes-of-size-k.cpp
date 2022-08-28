class Solution {
public:
    bool hasAllCodes(string s, int k) {
        int n = (int)s.size();
        int all = 1 << k;
        if(n - k + 1 < all)
            return 0;
        vector<char> vis(all, 0);
        for(int i = 0, msk = 0; i < n; ++i) {
            msk = (msk << 1 | (s[i] == '1')) & (all - 1);
            if(i >= k - 1)
                vis[msk] = 1;
        }
        for(char x : vis)
            if(!x)
                return 0;
        return 1;
    }
};
