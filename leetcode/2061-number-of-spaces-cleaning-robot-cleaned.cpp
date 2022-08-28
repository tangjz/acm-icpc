class Solution {
public:
    int numberOfCleanRooms(vector<vector<int>>& room) {
        const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
        int r = room.size(), c = room[0].size(), ans = 0;
        vector<vector<int> > msk(r, vector<int>(c));
        queue<vector<int> > que;
        auto upd = [&](int x, int y, int d) -> bool {
            if(x < 0 || x >= r || y < 0 || y >= c || room[x][y])
                return 0;
            if(((msk[x][y] >> d) & 1))
                return 1;
            ans += !msk[x][y];
            msk[x][y] |= 1 << d;
            que.push({x, y, d});
            return 1;
        };
        upd(0, 0, 0);
        while(!que.empty()) {
            auto &cur = que.front();
            int x = cur[0], y = cur[1], d = cur[2];
            que.pop();
            if(!upd(x + dx[d], y + dy[d], d))
                upd(x, y, (d + 1) & 3);
        }
        return ans;
    }
};
