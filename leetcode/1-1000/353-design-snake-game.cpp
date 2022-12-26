class SnakeGame {
    int r, c;
    pair<int, int> cur;
    map<pair<int, int>, int> vis;
    queue<pair<int, int> > que;
    vector<vector<int> >::const_iterator head, tail;
public:
    SnakeGame(int width, int height, vector<vector<int>>& food) {
        r = height;
        c = width;
        vis.clear();
        while(!que.empty())
            que.pop();
        cur = {0, 0};
        que.push(cur);
        head = food.begin();
        tail = food.end();
        vis[cur] = 1;
        vis[{(*head)[0], (*head)[1]}] = 2;
    }

    int move(string direction) {
        static const char *pat = "ULRD";
        static const int maxd = 4, dx[] = {-1, 0, 0, 1}, dy[] = {0, -1, 1, 0};
        int x, y;
        tie(x, y) = cur;
        for(int i = 0; i < maxd; ++i)
            if(direction[0] == pat[i]) {
                x += dx[i];
                y += dy[i];
                break;
            }
        if(x < 0 || x >= r || y < 0 || y >= c)
            return -1;
        cur = {x, y};
        auto it = vis.find(cur);
        if(it != vis.end() && it -> second == 2) {
            if((++head) != tail)
                vis[{(*head)[0], (*head)[1]}] = 2;
        } else {
            vis.erase(que.front());
            que.pop();
            it = vis.find(cur);
            if(it != vis.end())
                return -1;
        }
        que.push(cur);
        vis[cur] = 1;
        return que.size() - 1;
    }
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame* obj = new SnakeGame(width, height, food);
 * int param_1 = obj->move(direction);
 */
