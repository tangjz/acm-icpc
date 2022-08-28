class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = (int)tasks.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return tasks[u][0] < tasks[v][0];
        });
        typedef long long LL;
        LL cur = 0;
        priority_queue<pair<int, int> > que;
        vector<int> ret;
        for(int i = 0, j = 0; i < n; ++i) {
            if(que.empty() && cur < tasks[ord[j]][0]) {
                cur = tasks[ord[j]][0];
            }
            // printf("cur %lld\n", cur);
            while(j < n && cur >= tasks[ord[j]][0]) {
                // printf("add %d\n", ord[j]);
                que.push({-tasks[ord[j]][1], -ord[j]});
                ++j;
            }
            int u = -que.top().second;
            // printf("get %d\n", u);
            que.pop();
            cur += tasks[u][1];
            ret.push_back(u);
        }
        // puts("");
        return ret;
    }
};
