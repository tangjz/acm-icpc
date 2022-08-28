class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int ans = 0, pos = 0, rem = startFuel;
        priority_queue<int> que;
        stations.push_back({target, 0});
        for(auto &it: stations) {
            rem -= it[0] - pos;
            pos = it[0];
            while(rem < 0) {
                if(que.empty())
                    return -1;
                ++ans;
                rem += que.top();
                que.pop();
            }
            que.push(it[1]);
        }
        return ans;
    }
};
