class Solution {
public:
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        vector<int> ans = {-1, -1};
        set<vector<int> > vis;
        queue<vector<int> > que;
        if(firstPlayer > n / 2) {
            firstPlayer = n + 1 - firstPlayer;
            secondPlayer = n + 1 - secondPlayer;
            swap(firstPlayer, secondPlayer);
        }
        if(secondPlayer > n / 2 && firstPlayer > n + 1 - secondPlayer) {
            firstPlayer = n + 1 - firstPlayer;
            secondPlayer = n + 1 - secondPlayer;
            swap(firstPlayer, secondPlayer);
        }
        que.push({n, firstPlayer, secondPlayer, 1});
        vis.insert(que.back());
        while(!que.empty()) {
            vector<int> state = que.front();
            que.pop();
            int m = state[0], u = state[1], v = state[2];
            // printf("explore %d %d %d (%d)\n", m, u, v, state[3]);
            if(u == m + 1 - v) {
                int tmp = state[3];
                if(ans[0] == -1)
                    ans[0] = tmp;
                ans[1] = tmp;
                continue;
            }
            int x = u, y = v > m / 2 ? m + 1 - v : v;
            for(int i = 0; i < x; ++i)
                for(int j = 0; j < y - x; ++j) {
                    int mm = (m + 1) >> 1;
                    int p = i + 1, q = v > m / 2 ? mm + 1 - (y - 1 - i - j) : i + j + 2;
                    if(p > mm / 2) {
                        p = mm + 1 - p;
                        q = mm + 1 - q;
                        swap(p, q);
                    }
                    if(p > mm + 1 - q) {
                        p = mm + 1 - p;
                        q = mm + 1 - q;
                        swap(p, q);
                    }
                    // printf("find %d %d %d (%d)\n", mm, p, q, state[3] + 1);
                    vector<int> nxt = {mm, p, q, state[3] + 1};
                    if(vis.count(nxt))
                        continue;
                    vis.insert(nxt);
                    que.push(nxt);
                }
        }
        return ans;
    }
};
