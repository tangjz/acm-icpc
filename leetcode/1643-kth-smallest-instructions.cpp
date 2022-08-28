class Solution {
public:
    string kthSmallestPath(vector<int>& dst, int k) {
        int n = dst[0], m = dst[1];
        vector<vector<int> > ways(n + 1, vector<int>(m + 1));
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= m; ++j)
                ways[i][j] = !i && !j ? 1 : (i > 0 ? ways[i - 1][j] : 0) + (j > 0 ? ways[i][j - 1] : 0);
        string ret = "";
        while(n && m) {
            if(k > ways[n][m - 1]) {
                k -= ways[n][m - 1];
                ret.push_back('V');
                --n;
            } else {
                ret.push_back('H');
                --m;
            }
        }
        while(m--)
            ret.push_back('H');
        while(n--)
            ret.push_back('V');
        return ret;
    }
};
