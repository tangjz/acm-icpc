class Solution {
public:
    bool isPrintable(vector<vector<int>>& targetGrid) {
        int n = (int)targetGrid.size(), m = (int)targetGrid[0].size();
        unordered_map<int, vector<pair<int, int> > > vec;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                vec[targetGrid[i][j]].push_back({i, j});
        int ban = 0;
        while(ban < n * m) {
            bool found = 0;
            for(auto &it : vec) {
                int col = it.first;
                int xL = n, xR = 0, yL = m, yR = 0;
                for(auto &jt : it.second) {
                    xL = min(xL, jt.first);
                    xR = max(xR, jt.first);
                    yL = min(yL, jt.second);
                    yR = max(yR, jt.second);
                }
                int cnt = 0;
                for(int i = xL; i <= xR; ++i)
                    for(int j = yL; j <= yR; ++j)
                        cnt += targetGrid[i][j] == col || targetGrid[i][j] == -1;
                if(cnt == (xR - xL + 1) * (yR - yL + 1)) {
                    found = 1;
                    for(int i = xL; i <= xR; ++i)
                        for(int j = yL; j <= yR; ++j)
                            if(targetGrid[i][j] == col) {
                                ++ban;
                                targetGrid[i][j] = -1;
                            }
                    vec.erase(col);
                    break;
                }
            }
            if(!found)
                return 0;
        }
        return 1;
    }
};
