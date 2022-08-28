class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int n = g.size(), m = s.size(), tot = 0, ans = 0;
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        for(int i = 0, j = 0; i < m; ++i) {
            for( ; j < n && g[j] <= s[i]; ++j)
                g[tot++] = g[j];
            if(tot > 0) {
                --tot;
                ++ans;
            }
        }
        return ans;
    }
};
