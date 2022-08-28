class Solution {
public:
    int firstUniqChar(string s) {
        const int maxd = 26;
        int n = (int)s.length();
        vector<int> vis(maxd, -1);
        for(int i = 0; i < n; ++i) {
            int ch = s[i] - 'a';
            if(vis[ch] == -1) {
                vis[ch] = i;
            } else {
                vis[ch] = n;
            }
        }
        int ret = n;
        for(int i = 0; i < maxd; ++i)
            if(vis[i] != -1)
                ret = min(ret, vis[i]);
        return ret < n ? ret : -1;
    }
};
