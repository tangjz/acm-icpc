class Solution {
public:
    int minFlips(vector<vector<int>>& mat) {
        int n = (int)mat.size(), m = (int)mat[0].size();
        vector<int> trans;
        int fir = 0;
        for(int i = 0, idx = 0; i < n; ++i)
            for(int j = 0; j < m; ++j, ++idx) {
                int msk = 1 << idx;
                for(int dx = -1; dx <= 1; ++dx)
                    for(int dy = -1; dy <= 1; ++dy) {
                        if(!dx == !dy)
                            continue;
                        int x = i + dx, y = j + dy;
                        if(x < 0 || x >= n || y < 0 || y >= m)
                            continue;
                        msk |= 1 << (idx + dx * m + dy);
                    }
                trans.push_back(msk);
                fir |= (mat[i][j] == 1) << idx;
            }
        vector<int> dis(1 << (n * m), -1);
        queue<int> que;
        auto append = [&](int key, int val) {
            if(dis[key] != -1)
                return;
            dis[key] = val;
            que.push(key);
        };
        append(fir, 0);
        while(!que.empty()) {
            int msk = que.front(), dist = dis[msk];
            que.pop();
            for(int adt : trans)
                append(msk ^ adt, dist + 1);
            if(dis[0] != -1)
                break;
        }
        return dis[0];
    }
};
