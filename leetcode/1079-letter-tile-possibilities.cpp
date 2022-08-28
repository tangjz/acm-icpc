class Solution {
public:
    int numTilePossibilities(string tiles) {
        int n = tiles.size();
        unordered_map<char, int> ctr;
        for(char ch: tiles)
            ++ctr[ch];
        vector<vector<int> > bin(n + 1, vector<int>(n + 1));
        for(int i = 0; i <= n; ++i) {
            bin[i][0] = bin[i][i] = 1;
            for(int j = 1; j < i; ++j)
                bin[i][j] = bin[i - 1][j - 1] + bin[i - 1][j];
        }
        vector<int> f(n + 1, 0);
        f[0] = 1;
        for(auto &it: ctr) {
            vector<int> g(n + 1, 0);
            for(int i = 0; i <= it.second; ++i)
                for(int j = 0; i + j <= n; ++j)
                    g[i + j] += f[j] * bin[i + j][j];
            f = move(g);
        }
        int ans = 0;
        for(int i = 1; i <= n; ++i)
            ans += f[i];
        return ans;
    }
};
