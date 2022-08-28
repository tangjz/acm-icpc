class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& info, int m) {
        int n = (int)info.size();
        priority_queue<pair<double, int> > que;
        for(int i = 0; i < n; ++i) {
            auto &it = info[i];
            int u = it[0], v = it[1];
            que.push(make_pair((u + 1) / (v + 1.0) - (u + 0) / (v + 0.0), i));
        }
        while(m--) {
            int i = que.top().second;
            // printf("inc %d %f\n", i, que.top().first);
            que.pop();
            auto &it = info[i];
            int u = ++it[0], v = ++it[1];
            que.push(make_pair((u + 1) / (v + 1.0) - (u + 0) / (v + 0.0), i));
        }
        double ans = 0;
        for(auto &it: info)
            ans += (double)it[0] / it[1];
        return ans / n;
    }
};
