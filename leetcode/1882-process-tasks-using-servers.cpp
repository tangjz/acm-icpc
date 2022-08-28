class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = (int)servers.size(), m = (int)tasks.size(), tim = 0;
        typedef pair<int, int> PII;
        priority_queue<PII, vector<PII>, greater<PII> > busy, idle;
        for(int i = 0; i < n; ++i) {
            idle.push({servers[i], i});
        }
        vector<int> ans;
        for(int i = 0; i < m; ++i) {
            tim = max(tim, i);
            while(true) {
                while(!busy.empty() && busy.top().first <= tim) {
                    int j = busy.top().second;
                    busy.pop();
                    idle.push({servers[j], j});
                }
                if(!idle.empty())
                    break;
                tim = max(tim, busy.top().first);
            }
            int j = idle.top().second;
            idle.pop();
            ans.push_back(j);
            busy.push({tim + tasks[i], j});
        }
        return ans;
    }
};
