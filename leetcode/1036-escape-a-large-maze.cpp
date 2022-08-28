class Solution {
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        const int maxv = (int)1e6;
        vector<int> shape(2);
        for(int i = 0; i < 2; ++i) {
            vector<int> que = {source[i], target[i]};
            for(auto &it: blocked) {
                que.push_back(it[i]);
            }
            shape[i] = que.size();
            for(int j = 0; j < shape[i]; ++j) {
                if(que[j] + 1 < maxv)
                    que.push_back(que[j] + 1);
                if(que[j] > 0)
                    que.push_back(que[j] - 1);
            }
            sort(que.begin(), que.end());
            que.erase(unique(que.begin(), que.end()), que.end());
            shape[i] = que.size();
            auto convert = [&](int &x) {
                x = lower_bound(que.begin(), que.end(), x) - que.begin();
            };
            convert(source[i]);
            convert(target[i]);
            for(auto &it: blocked)
                convert(it[i]);
        }
        vector<vector<bool> > vis(shape[0], vector<bool>(shape[1]));
        queue<pair<int, int> > que;
        auto append = [&](int x, int y) {
            if(x < 0 || x >= shape[0] || y < 0 || y >= shape[1] || vis[x][y])
                return;
            vis[x][y] = 1;
            que.push({x, y});
        };
        for(auto &it: blocked)
            vis[it[0]][it[1]] = 1;
        append(source[0], source[1]);
        while(!que.empty()) {
            int x, y;
            tie(x, y) = que.front();
            que.pop();
            for(int dx = -1; dx <= 1; ++dx) {
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    append(x + dx, y + dy);
                }
            }
        }
        return vis[target[0]][target[1]];
    }
};
