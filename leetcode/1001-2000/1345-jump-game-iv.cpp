class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = (int)arr.size();
        unordered_map<int, vector<int> > pos;
        for(int i = 0; i < n; ++i)
            pos[arr[i]].push_back(i);
        vector<int> dis(n, INT_MAX);
        queue<int> que;
        auto append = [&](int u, int dist) {
            if(dis[u] < INT_MAX)
                return;
            dis[u] = dist;
            que.push(u);
        };
        append(0, 0);
        while(dis[n - 1] == INT_MAX && !que.empty()) {
            int u = que.front(), nxt = dis[u] + 1;
            que.pop();
            if(u + 1 < n)
                append(u + 1, nxt);
            if(u - 1 >= 0)
                append(u - 1, nxt);
            vector<int> &vec = pos[arr[u]];
            if(!vec.empty()) {
                for(int v : vec)
                    append(v, nxt);
                vector<int>().swap(vec);
            }
        }
        return dis[n - 1];
    }
};
