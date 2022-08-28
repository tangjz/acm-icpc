class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int n = image.size(), m = image[0].size();
        int col = image[sr][sc];
        vector<pair<int, int> > que;
        image[sr][sc] = -1;
        que.push_back({sr, sc});
        for(int i = 0; i < (int)que.size(); ++i) {
            int x, y;
            tie(x, y) = que[i];
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!!dx == !!dy)
                        continue;
                    int xx = x + dx, yy = y + dy;
                    if(xx < 0 || xx >= n || yy < 0 || yy >= m || image[xx][yy] != col)
                        continue;
                    image[xx][yy] = -1;
                    que.push_back({xx, yy});
                }
        }
        for(auto &it: que)
            image[it.first][it.second] = newColor;
        return move(image);
    }
};
