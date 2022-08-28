class Solution {
public:
    int processTasks(vector<vector<int>>& tasks) {
        const int INF = 0x3f3f3f3f;
        sort(tasks.begin(), tasks.end());
        tasks.push_back({INF, INF, 0});
        int ans = 0;
        priority_queue<pair<int, int> > que;
        for(auto &it: tasks) {
            while(!que.empty() && -que.top().first + ans < it[0])
                if(-que.top().first + ans < que.top().second) {
                    ans = min(que.top().second, it[0]) + que.top().first;
                } else {
                    que.pop();
                }
            que.push({-(it[1] - it[2] + 1 - ans), it[1] + 1});
        }
        return ans;
    }
};
