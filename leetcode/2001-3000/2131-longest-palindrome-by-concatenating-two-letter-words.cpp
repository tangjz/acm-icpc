class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        const int maxc = 26;
        static int ctr[maxc + 1][maxc + 1] = {};
        memset(ctr, 0, sizeof ctr);
        for(auto &it: words) {
            int u = it[0] - 'a';
            int v = it[1] - 'a';
            ++ctr[u][v];
        }
        int ans = 0;
        for(int i = 0; i < maxc; ++i) {
            if(!ctr[i][i])
                continue;
            --ctr[i][i];
            int tmp = 0;
            for(int x = 0; x < maxc; ++x) {
                tmp += ctr[x][x] >> 1;
                for(int y = x + 1; y < maxc; ++y)
                    tmp += min(ctr[x][y], ctr[y][x]);
            }
            tmp = tmp << 1 | 1;
            ans = max(ans, tmp);
            ++ctr[i][i];
        }
        int tmp = 0;
        for(int x = 0; x < maxc; ++x) {
            tmp += ctr[x][x] >> 1;
            for(int y = x + 1; y < maxc; ++y)
                tmp += min(ctr[x][y], ctr[y][x]);
        }
        tmp = tmp << 1;
        ans = max(ans, tmp);
        return ans << 1;
    }
};
