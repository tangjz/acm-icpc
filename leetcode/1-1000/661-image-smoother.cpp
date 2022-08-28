class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        int r = img.size(), c = img[0].size();
        vector<vector<int> > ret(r, vector<int>(c));
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j) {
                int cnt = 0, sum = 0;
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        int x = i + dx, y = j + dy;
                        if(x < 0 || x >= r || y < 0 || y >= c)
                            continue;
                        ++cnt;
                        sum += img[x][y];
                    }
                ret[i][j] = sum / cnt;
            }
        return ret;
    }
};
