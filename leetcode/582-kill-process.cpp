class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        int n = pid.size();
        unordered_map<int, vector<int> > e;
        for(int i = 0; i < n; ++i)
            e[ppid[i]].push_back(pid[i]);
        vector<int> que = {kill};
        for(int i = 0; i < (int)que.size(); ++i) {
            int u = que[i];
            for(int v: e[u])
                que.push_back(v);
        }
        return que;
    }
};
