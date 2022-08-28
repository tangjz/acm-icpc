class Solution {
public:
    long long minCost(vector<int>& nums, vector<int>& costs) {
        typedef long long LL;
        static const LL INF = 0x3f3f3f3f3f3f3f3fLL;
        int n = nums.size();
        vector<int> pR(n), qR(n);
        for(int i = n - 1; i >= 0; --i) {
            for(pR[i] = i + 1; pR[i] < n && nums[pR[i]] < nums[i]; pR[i] = pR[pR[i]]);
            for(qR[i] = i + 1; qR[i] < n && nums[qR[i]] >= nums[i]; qR[i] = qR[qR[i]]);
        }
        vector<bool> vis(n);
        vector<LL> dis(n, INF);
        priority_queue<pair<LL, int> > que;
        auto upd = [&](int u, LL dist) {
            if(u >= n)
                return;
            dist += costs[u];
            if(dis[u] > dist) {
                dis[u] = dist;
                que.push({-dis[u], u});
            }
        };
        upd(0, 0);
        while(!que.empty()) {
            int u = que.top().second;
            que.pop();
            if(vis[u])
                continue;
            vis[u] = 1;
            upd(pR[u], dis[u]);
            upd(qR[u], dis[u]);
        }
        return dis.back() - dis.front();
    }
};
