class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        const int maxv = 1001;
        vector<int> dis(maxv, -1);
        queue<int> que;
        auto upd = [&](int x, int d) {
            if(x < 0 || x >= maxv || dis[x] != -1)
                return;
            dis[x] = d;
            que.push(x);
        };
        upd(start, 0);
        while(!que.empty()) {
            int u = que.front(), nxt = dis[u] + 1;
            que.pop();
            for(int x: nums) {
                upd(u + x, nxt);
                upd(u - x, nxt);
                upd(u ^ x, nxt);
            }
        }
        if(goal >= 0 && goal < maxv)
            return dis[goal];
        int ans = -1;
        auto chk = [&](int x) {
            if(x < 0 || x >= maxv || dis[x] == -1)
                return;
            if(ans == -1 || ans > dis[x] + 1)
                ans = dis[x] + 1;
        };
        for(int x: nums) {
            chk(goal + x);
            chk(goal - x);
            chk(goal ^ x);
        }
        return ans;
    }
};
