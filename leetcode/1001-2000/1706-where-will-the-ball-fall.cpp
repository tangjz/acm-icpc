class Solution {
public:
    vector<int> findBall(vector<vector<int>>& grid) {
        int n = (int)grid.size(), m = (int)grid[0].size();
        vector<int> ret;
        for(int i = 0; i < m; ++i) {
            int px = 0, py = i, pz = 0;
            while(!(px == n - 1 && pz == 1)) {
                if(grid[px][py] == 1) {
                    if(pz == 0) {
                        if(py + 1 == m || grid[px][py + 1] == -1)
                            break;
                        ++py;
                        pz = 1;
                    } else {
                        ++px;
                        pz = 0;
                    }
                } else {
                    if(pz == 0) {
                        if(py - 1 < 0 || grid[px][py - 1] == 1)
                            break;
                        --py;
                        pz = 1;
                    } else {
                        ++px;
                        pz = 0;
                    }
                }
            }
            ret.push_back(px == n - 1 && pz == 1 ? py : -1);
        }
        return ret;
    }
};
