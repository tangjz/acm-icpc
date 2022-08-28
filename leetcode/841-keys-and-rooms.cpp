class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<bool> vis(n);
        vector<int> que;
        vis[0] = 1;
        que.push_back(0);
        for(int i = 0; i < (int)que.size(); ++i) {
            int u = que[i];
            for(int v: rooms[u])
                if(!vis[v]) {
                    vis[v] = 1;
                    que.push_back(v);
                }
        }
        return (int)que.size() == n;
    }
};
