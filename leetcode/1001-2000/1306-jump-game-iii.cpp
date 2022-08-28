class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = (int)arr.size();
        vector<int> vis(n);
        queue<int> que;
        auto append = [&](int u) {
            if(u < 0 || u >= n || vis[u])
                return;
            vis[u] = 1;
            que.push(u);
        };
        append(start);
        while(!que.empty()) {
            int u = que.front(), dt = arr[u];
            que.pop();
            append(u - dt);
            append(u + dt);
        }
        for(int i = 0; i < n; ++i)
            if(!arr[i] && vis[i])
                return 1;
        return 0;
    }
};
