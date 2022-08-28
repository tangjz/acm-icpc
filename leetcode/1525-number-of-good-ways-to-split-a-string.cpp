class Solution {
public:
    int numSplits(string s) {
        const int maxd = 26;
        int ans = 0, len = (int)s.size();
        vector<int> cL(len), vis(maxd);
        for(int i = 0, cnt = 0; i < len; ++i) {
            int o = s[i] - 'a';
            if(!vis[o]) {
                vis[o] = 1;
                ++cnt;
            }
            cL[i] = cnt;
        }
        vis.assign(maxd, 0);
        for(int i = len - 1, cnt = 0; i > 0; --i) {
            int o = s[i] - 'a';
            if(!vis[o]) {
                vis[o] = 1;
                ++cnt;
            }
            ans += cnt == cL[i - 1];
        }
        return ans;
    }
};
