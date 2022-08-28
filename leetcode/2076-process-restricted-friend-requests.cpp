class Solution {
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& lim, vector<vector<int>>& req) {
        vector<int> idx(n);
        vector<vector<int> > sp(n);
        for(int i = 0; i < n; ++i) {
            idx[i] = i;
            sp[i] = {i};
        }
        vector<bool> ans;
        for(auto &it: req) {
            int u = it[0], v = it[1];
            if(idx[u] == idx[v]) {
                ans.push_back(true);
                continue;
            }
            bool ban = false;
            for(auto &jt: lim) {
                int x = jt[0], y = jt[1];
                if(idx[x] == idx[u] && idx[y] == idx[v]) {
                    ban = true;
                    break;
                }
                if(idx[x] == idx[v] && idx[y] == idx[u]) {
                    ban = true;
                    break;
                }
            }
            ans.push_back(!ban);
            if(ban) {
                continue;
            }
            u = idx[u];
            v = idx[v];
            for(int x: sp[v]) {
                idx[x] = u;
                sp[u].push_back(x);
            }
            vector<int>().swap(sp[v]);
        }
        return ans;
    }
};
