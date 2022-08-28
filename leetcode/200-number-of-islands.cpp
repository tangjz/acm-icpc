class Solution {
private:
    int r, c;
    vector<vector<char> > g;
    void dfs(int x, int y) {
        if(x < 0 || x >= r || y < 0 || y >= c || g[x][y] == '0')
            return;
        g[x][y] = '0';
        dfs(x - 1, y);
        dfs(x, y - 1);
        dfs(x, y + 1);
        dfs(x + 1, y);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int ans = 0;
        g = grid;
        r = (int)g.size();
        if(!r)
            return 0;
        c = (int)g[0].size();
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                if(g[i][j] == '0')
                    continue;
                dfs(i, j);
                ++ans;
            }
        return ans;
    }
};
