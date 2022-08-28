class Solution {
public:
    int digArtifacts(int n, vector<vector<int>>& artifacts, vector<vector<int>>& dig) {
        vector<vector<bool> > vis(n, vector<bool>(n));
        for(auto &it: dig)
            vis[it[0]][it[1]] = 1;
        int ans = 0;
        for(auto &it: artifacts) {
            int xL = it[0], yL = it[1];
            int xR = it[2], yR = it[3];
            int rem = (xR - xL + 1) * (yR - yL + 1);
            for(int x = xL; x <= xR; ++x)
                for(int y = yL; y <= yR; ++y)
                    rem -= vis[x][y];
            if(!rem)
                ++ans;
        }
        return ans;
    }
};
