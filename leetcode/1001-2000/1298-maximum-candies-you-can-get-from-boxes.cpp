class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        int ret = 0;
        queue<int> que;
        auto append = [&](int u) {
            if(status[u] != 3)
                return;
            status[u] |= 4;
            que.push(u);
            ret += candies[u];
        };
        for(int u : initialBoxes) {
            status[u] |= 2;
            append(u);
        }
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int v : keys[u]) {
                status[v] |= 1;
                append(v);
            }
            for(int v : containedBoxes[u]) {
                status[v] |= 2;
                append(v);
            }
        }
        return ret;
    }
};
